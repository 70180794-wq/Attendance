#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
   ofstream name("lkg.txt");
   name<<" you hate me"<<endl;
   name<<"ojk its fine"<<endl;
   name.close();
    string st;
    ifstream you("lkg.txt" );
       while(getline(you,st)){
    cout<<st;
}you.close();
}