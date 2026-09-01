#include<iostream>
using namespace std;
class car{
    public:
    int seat;
    float cc;
    string name;
    
   car(int seat,float cc, string name){
       this-> name=name;
       this-> seat=seat;
        this->cc=cc;
   }
}; 
    
int  main(){
    car s1(5,120,"BMW");
    
    cout<<s1.name<<""<<s1.seat<<""<<s1.cc<<endl;
    }