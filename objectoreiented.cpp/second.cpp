#include<iostream>
using namespace std;
class king{
    private:
    int a1,b1,c1;
    public:
    int e1,c2;
     void average(int a1,int b1,int c1,int e1,int c2);
    void displaynumber{
        cout<<"the number for a1 is "<<a1<<endl;
        cout<<"the number for b1 is "<<b1<<endl;
        cout<<"the number for c1 is "<<c1<<endl;
        cout<<"the number for e1 is "<<e1<<endl;
        cout<<"the number for c2 is "<<c2<<endl;

    }
};
int king ::average(int a1,int b1,int c1,int e1,int c2){
    a=a1;
    b=b1;
    c=c1;
    d=e1;
    e=c2;
    int sum=a+b+C+d+e;
    int average=sum/5;
    return average;
}
int main(){
    king zeeshan;
    zeeshan.e1=7;
    zeeshan.c2=9;
    zeeshan.average(67,98,67);

    zeeshan.displaynumber;

}