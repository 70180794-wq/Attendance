#include <iostream>
using namespace std;
int main(){
    int marks[]= {77,89,89};
      for(int i=0;i<3; i++){
        cout<<"the value of marks is "<<marks[i]<<endl;
      }
       marks[2]=99;
       int* o= marks;
       cout<<"the markse of this "<<*(o)<<endl;
              o++;
       cout<< *o<<endl;
       o--;
       cout<< *o<<endl;
       cout<< *(marks+2);
      

       int x = 50, y = 60, z = 70;
int *ptr = nullptr;
cout << x << " " << y << " " << z << endl;
ptr = &x;
*ptr *= 10;
ptr = &y;
*ptr *= 5;
ptr = &z;
*ptr *= 2;
cout << x << " " << y << " " << z << endl;
}