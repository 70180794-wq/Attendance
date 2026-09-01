#include<iostream>
using namespace std;
class Rectangle{
    private:
    int length;
    int width;
   public:
        Rectangle(int l,int w){
            length=l;
            width=w;
            
      }
        
        int area(){
                return length*width;
            }
            int perimeter(){
                return 2*(length +width);
            }
        

};


int main(){
     Rectangle a(6,8);
      Rectangle b=a;
      b.length =6;
    cout<< a.area()<<endl;
    cout<<a.perimeter()<<endl;
    cout<<b.area()<<endl;

     }