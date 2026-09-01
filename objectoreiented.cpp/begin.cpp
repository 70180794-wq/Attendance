#include<iostream>
using namespace std;
//class abc{
  //public:
  //static int number;
//};
  // int abc::number=0;
  class student{
  
    public:
    string name;
    int sub1;
    int sub2;
    int sub3;
    student(string n,int s1,int s2,int s3 ){
      name=n;
      sub1=s1;
      sub2=s2;
      sub3=s3;
    }
    };
    void calculate_average (){
      student s1("ALI",67,56,89);
      float avg=(s1.sub1+s1.sub2+s1.sub3)/3;
      char grade;
      if (avg>85){
        grade='a';
      }else if(avg>75){
       grade='b';
      }

      cout<<"average"<<avg<<endl;
    cout<<"grade"<<grade<<endl;
    }
    

int main(){
    calculate_average();
 // abc o1,t1;
 // abc::number=56;
 // cout<<o1.number<<endl;
 // cout<<t1.number<<endl;
 // o1.number=15;
 // cout<<o1.number<<endl;
 // cout<<t1.number<<endl;
}