#include<iostream>
using namespace std;
int main(){
	int sum=0;
	int student[5];
	for(int i=0;i<5;i++){
		cin>>student[i];
		cout<<"the marks for student"<<i+1<<":"<<"is"<<student[i]<<endl;
		sum+=student[i];
	
	}cout<<"the total sum of student is "<<sum<<endl;
	return 0;
}