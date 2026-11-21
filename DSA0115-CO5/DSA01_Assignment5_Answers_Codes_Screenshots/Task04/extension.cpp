#include <iostream>
#include <string>
#include <unordered_map>
class Bill {protected:std::string patient;public:explicit Bill(std::string p):patient(std::move(p)){}virtual ~Bill()=default;virtual double total()const=0;virtual std::string type()const=0;};
class OutPatient:public Bill{double consult,tests;public:OutPatient(std::string p,double c,double t):Bill(std::move(p)),consult(c),tests(t){}double total()const override{return consult+tests;}std::string type()const override{return "OP";}};
class EmergencyBill:public Bill{double base,hours,rate;public:EmergencyBill(std::string p,double b,double h,double r):Bill(std::move(p)),base(b),hours(h),rate(r){}double total()const override{return base+hours*rate;}std::string type()const override{return "Emergency";}};
class Payer{public:virtual ~Payer()=default;virtual double amountCovered(const Bill& b)const=0;};
class SelfPay:public Payer{public:double amountCovered(const Bill& b)const override{return b.total();}};
class CorporatePayer:public Payer{double fraction;public:explicit CorporatePayer(double f):fraction(f){}double amountCovered(const Bill& b)const override{return b.total()*fraction;}};
int main(){EmergencyBill b("Raju",1000,3,500);SelfPay self;CorporatePayer corp(0.8);std::cout<<b.type()<<" total="<<b.total()<<'\n';std::cout<<"self covered="<<self.amountCovered(b)<<'\n';std::cout<<"corporate covered="<<corp.amountCovered(b)<<'\n';}
