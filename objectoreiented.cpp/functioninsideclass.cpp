#include<iostream>
using namespace std;
class player{
    public:
    string name;
    float runs;
    int avg;
    player(string n,int r,int a){
        name=n;
        runs=r;
        avg=a;
    }
    void print(){
        cout<<"the runs are"<<runs<<endl;
        cout<<"the average are"<<avg<<endl;
        cout<<"the name are"<<name<<endl;

    }
 int matches(){
      return runs/avg;
 }
};
int main(){
 player p1("zeeshan",18000,56);
 player p2("ali", 20000,69);
 p1.print();
 p2.print();
 // you can also change the name or any information by this pattern 
 p1.name="king";
 p1.print(); 
 cout<<p1.matches()<<endl;
}