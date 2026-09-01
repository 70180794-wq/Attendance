#include <iostream>
#include<iomanip>
#include<string>

using namespace std;
const int number=50;
int student[number];
int roll_number[number];
float marks[number];
string name[number];
int count=0;
 void displaymenu();
void add_student();
void display_result();
void check_result();
int linearsearch(int roll);
bool rolls_number(int roll);
bool validate_marks(float m);
int main(){
    displaymenu();
       cout<<"===================="<<endl;

       cout<<" STUDENT EXAM RESULT"<<endl;
       cout<<" ===================="<<endl;
       int choice;
        do{cout<<"enter your choice"<<endl;
       cin>>choice; 
       switch(choice){
        case 1:
            displaymenu(); 
             break;
        case 2:
           add_student();
             break;
        case 3:
            cout<<"The student results are shown below:"<<endl;
             display_result();
             break;
        case 4:
            cout<<"your result is :"<<endl;
           check_result();  
           break;
        case 5:
                cout << "Thank you for using the Exam Result Management System!"<<endl;
                cout << "Exiting..."<<endl;
                return 0;
        default:  
        cout<<"invalid choice please enter again"<<endl;
       }
    }while(true);

}
void displaymenu(){
    cout<<"1. for to show menu again"<<endl;
    cout<<"2. for to add student "<<endl;
    cout<<"3. for to display result of an student"<<endl;
    cout<<"4. for to check the  result of student "<<endl;
    cout<<"5. for to extist from program"<<endl;

}
 bool rolls_number( int roll){
    if(roll <=0 ){
        cout<<" The roll number cannot be negative. "<<endl;
        cout<<"please enter the positive roll number."<<endl;
        return false;
    }
    return true;
 }  

  bool validate_marks(float m){
    if(m<0){
         cout<<"the marks cannot be negetive ."<<endl;
         cout<<"please enter the postive marks."<<endl;
         return false;

    }return true;
  } 

     void add_student(){
    int r;
    float m;
    string n;
    if (count >= number){
        cout <<"student limit  reached."<<endl;
        cout<<"more student can not be added"<<endl;
        return;
    }
    cout <<"enter the student roll nunber"<<endl;
    cin>>r;
    do{
        if (r <= 0){
            cout<<"The Roll Number can not be negetive."<<endl;
            cout<<"please enter the valid roll number."<<endl;
            return;
        }}while(r<0);
        if ( linearsearch(r) !=-1 ){
            cout<<" The  Roll number is already given to other student. "<<endl;
            cout<<" please give other Roll number to the student."<<endl;
            return;
        }
        cout<<"enter the student marks"<<endl;
    cin>>m;
    do{
    if (m<0 || m>100){
        cout<<"The marks remain between 0 to 100 "<<endl;
        cout<<"please enter the marks again correctly"<<endl;
        return;
        cin>>m;
    }}while(m<0 ||m>100);
    
    cout<<"enter the name of student "<<endl;
    cin.ignore();
    getline (cin,n); 

        name[count]= n;
      roll_number[count]=r;
        marks[count]=m;
        count++;
      cout<<" student add successfully."<<endl;
      cout<<"total student are:"<<count<<endl;
   
} 
 void display_result(){
    cout<<"=================="<<endl;
    cout<<"  EXAM RESULTS"<<endl;
    cout<<"=================="<<endl;
    if(count ==0){
        cout<<"no student record found"<<endl;
        cout<<"please add the student first "<<endl;
            }
            cout<< left << setw(15) << "ROLL NUMBER"
            <<setw(13) << "NAME"
            << setw(15) << "MARKS OBTAINED" <<endl;

            for(int i=0;i < count;i++){
                cout<< left << setw(15) << roll_number[i]
                << setw(13) << name[i]
                <<fixed<<setprecision(2)<< setw(13) << marks[i] <<endl;
                        }
         cout<<"================="<<endl;
         cout<<"total student   :"<<count<<endl;               

 } 
     int linearsearch(int roll){
        for(int i=0;i<count;i++){
            if(roll_number[i]==roll){
                return i;
            }
        }
        return -1;
     }
  void check_result(){
    int rollnumber;
    int index;

    cout<<"===================="<<endl;

    cout<<" SEARCH STUDENT RESULT"<<endl;

    cout<<"====================="<<endl;

    if (count == 0){
        cout<<"no student record found "<<endl;
        cout<<"please add the student first "<<endl;
        return; 
    }
    cout<<"enter the rollnumber"<<endl;
    cin>>rollnumber;
           index=linearsearch(rollnumber);
           if(index != -1){
            cout<<"================="<<endl;

            cout<<"STUDENT RESULT FOUND"<<endl;

            cout<<"=================="<<endl;
            cout<<"ROLL NUMBER   :"<< roll_number[index]<<endl;
            cout<<"STUDENT NAME    :"<< name[index]<<endl;
            cout<< fixed << setprecision(2) <<endl;
            cout<<"STUDENT MARKS   :"<< marks[index]<<endl;
            cout<<"========================="<<endl;
            return;
            
           }else{
            cout<<"student with this roll number"<<rollnumber<<"not found"<<endl;
            cout<<"please check the roll number and then check result again "<<endl;
           }
          }
