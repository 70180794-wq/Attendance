#include<iostream>
using namespace std;
class asad{
    private:
     int a,b,c;
     public:
     int e,j;
     void calculate(int a1,int b1, int c1);

     void average(){
             cout <<"the value of a is"<<a<<endl;
             cout<<"the value of b is"<<b<<endl;
             cout<<"the value of c is"<<c<<endl;
             cout<<"the value of e is"<<e<<endl;
             cout<<"the value of j is"<<j<<endl;
     }
};
    void asad :: calculate(int a1,int b1, int c1){
        a=a1;
        b=b1;
        c=c1;
        }
int main(){
    asad employee;
    employee.e=5;
    employee.j=7;
    employee.calculate(7,8,9); 
    employee.average();
    return 0;
}