#include<iostream>
using namespace std;
class car{
    public:
    int seat;
    float cc;
    string name;
    car(){

    }//default contructor
    car(int s,float c, string n){
        name=n;
        seat=s;
        cc=c;
    }// parameterized constructor

   car(int s, string n){
        name=n;
        seat=s;
   }
}; 
     void change (car &s){
        s.name = "audi";
     } 
void display(car s){
    cout<<s.seat<<"cc"<<s.cc<<"name"<<s.name<<endl;
}
int  main(){
    car s1(5,120,"BMW");
    //s1.seat=5;
    //s1.cc=120;
    //s1.name="BMW";
    car s2;
    s1.seat=5;
    s1.cc=120;
    s1.name="BMW";

    car s3(5,"BMW");
  // now build a copy constructor
      car s5(s1);// deep constructor
      cout<<s5.seat<<" " <<  s5.cc<<""<<s5.name;


    display( s1);
    change( s1);
    display(s1);
    display (s2);
    display(s3);
}