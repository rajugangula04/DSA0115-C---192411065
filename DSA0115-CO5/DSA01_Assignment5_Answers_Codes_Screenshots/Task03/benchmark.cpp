#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <iomanip>
struct Base { virtual ~Base()=default; virtual double total() const=0; };
struct OP:Base { double a,b; OP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct IP:Base { double days,rate,surgery; IP(double d,double r,double s):days(d),rate(r),surgery(s){} double total()const override{return days*rate+surgery;} };
struct Record { int type; double a,b,c; double total()const {switch(type){case 0:return a+b;default:return a*b+c;}} };
template<class F> double measure(F f){auto s=std::chrono::steady_clock::now();volatile double result=f();auto e=std::chrono::steady_clock::now();(void)result;return std::chrono::duration<double,std::milli>(e-s).count();}
int main(){
 for(int n:{1000,1000000,10000000}){
  std::vector<std::unique_ptr<Base>> v;v.reserve(n);std::vector<Record> r;r.reserve(n);
  for(int i=0;i<n;++i){if(i%2==0){v.push_back(std::make_unique<OP>(500,1200));r.push_back({0,500,1200,0});}else{v.push_back(std::make_unique<IP>(3,2500,40000));r.push_back({1,3,2500,40000});}}
  double tv=measure([&]{double s=0;for(auto& x:v)s+=x->total();return s;});
  double ts=measure([&]{double s=0;for(auto& x:r)s+=x.total();return s;});
  double sv=0,ss=0;for(auto& x:v)sv+=x->total();for(auto& x:r)ss+=x.total();
  std::cout<<"n="<<n<<" virtual_ms="<<tv<<" switch_ms="<<ts<<" totals_equal="<<(sv==ss)<<" total="<<sv<<'\n';
 }
 for(int pct:{0,1,50}){
  constexpr int n=1000000;int invalidEvery=pct==0?0:(pct==1?100:2); 
  double ret=measure([&]{long count=0;for(int i=0;i<n;++i){bool bad=invalidEvery && i%invalidEvery==0;if(!bad)++count;}return static_cast<double>(count);});
  double exc=measure([&]{long count=0;for(int i=0;i<n;++i){try{if(invalidEvery && i%invalidEvery==0)throw std::runtime_error("invalid");++count;}catch(const std::exception&){} }return static_cast<double>(count);});
  std::cout<<"invalid="<<pct<<"% return_ms="<<ret<<" exception_ms="<<exc<<'\n';
 }
}
