#include <iostream>
#include <stdexcept>
#include <string>
#include <new>
struct Resource { ~Resource(){std::cout << "resource released\n";} };
double parseAmount(const std::string& s){return std::stod(s);}
void validate(double x){if(x<0)throw std::invalid_argument("negative charge");if(x>1000000)throw std::out_of_range("claim above limit");}
int main(){
 for(const std::string s:{"-5","2000000","abc","100"}){
  try{Resource r;double x=parseAmount(s);validate(x);std::cout << "valid " << x << '\n';}
  catch(const std::invalid_argument& e){std::cout << "invalid argument: " << e.what() << '\n';}
  catch(const std::out_of_range& e){std::cout << "out of range: " << e.what() << '\n';}
  catch(...){std::cout << "unexpected error\n";}
 }
 try{std::size_t n=static_cast<std::size_t>(-1)/sizeof(int);int* p=new int[n];delete[] p;}
 catch(const std::bad_alloc&){std::cout << "allocation failure caught\n";}
 catch(const std::exception& e){std::cout << "allocation request failed: " << e.what() << '\n';}
 catch(...){std::cout << "top-level catch-all\n";}
}
