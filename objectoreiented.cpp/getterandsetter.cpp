#include<iostream>
using namespace std;
// set use to modifies the private data member 
// get use to return the or display the value and to read
class Ali{
  private:
   int age;
  public:
    void setage(int a){
        if (a<5 && a>5){
            age = a;

        }else{
            cout<<"no age is here"<<endl;
        }

    }
    };

int main(){
 Ali s;
 s.setage(9);
 
}