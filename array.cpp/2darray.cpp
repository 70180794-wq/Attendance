#include <iostream>
using namespace std;
int main(){
	int studentmarks[5][6];
	int sum=0;
	int average=0;
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			cin>>studentmarks[i][j];
						sum+=studentmarks[i][j];	
						cout<<"the marks of student "<<i+1<<"is  :"<<studentmarks[i][j]<<endl;	
							}
	}	
	cout<<"the total marks of student are  :"<<sum<<endl;
	average=sum/5;
	cout<<"the average of five student is  :"<<average<<endl;
}