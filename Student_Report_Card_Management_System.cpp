#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "your password";
const char* DB = "mydb";

class Student{
private:
 string Name, RollNo, Grade;
 float Avg;	
 public:
 	
  Student(string name, string rollNo, float avg, string grade){
 Name = name;
 RollNo = rollNo;
 Avg = avg;
 Grade = grade;
		}
		
string getName(){
 return Name;
}

string getRollNo(){
 return RollNo;
}

float getAvg(){
 return Avg;
}

string getGrade(){
 return Grade;
}
 
};

report(MYSQL* conn){
string rollNo, grade;
int sub1,sub2,sub3,total;
float avg;
cout<<"Enter RollNo: ";
cin>>rollNo;
cout<<"Enter Number of Subject1: ";
cin>>sub1;
cout<<"Enter Number of Subject2: ";
cin>>sub2;
cout<<"Enter Number of Subject3: ";
cin>>sub3;
total = sub1+sub2+sub3;
avg = total/3;
if(avg>=90){
grade = "A+";	
}
else if(avg >= 80 && avg <90){
	grade = "A";
}
else if(avg >= 70 && avg <80){
	grade = "B+";
}
else if(avg >= 60 && avg <70){
	grade = "B";
}
else if(avg >= 50 && avg <60){
	grade = "C";
}
else if(avg >= 40 && avg <50){
	grade = "D";
}
else if(avg < 40){
	grade = "F";
}
stringstream ss;
ss<<avg;
string Savg = ss.str();

string update = "UPDATE Student SET Avg = '"+Savg+"', Grade = '"+grade+"' WHERE RollNo= '"+rollNo+"'";
if(mysql_query(conn,update.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
string display= "SELECT * FROM Student WHERE RollNO='"+rollNo+"' ";
if(mysql_query(conn,display.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
MYSQL_RES* res;
res = mysql_store_result(conn);	
if(res){
	int num = mysql_num_fields(res);
	MYSQL_ROW row;
 cout<<"\t|  ID  |"<<" Name |"<<"\t Avg |"<<" Grade"<<endl<<endl;
 while(row=mysql_fetch_row(res)){
 for(int i=0; i<num; i++){
 	cout<<"\t"<<row[i];
 }	
 }//while	
}//if res
}//nested else
}//outer else
	
}//function
int main(){
	
MYSQL* conn;
conn = mysql_init(NULL);
if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL,0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Logged in Database"<<endl;
}	
Sleep(3000);

 Student s1("Ali", "ab123", 0.0,"NULL");
 Student s2("Ahmad", "bc234", 0.0,"NULL");
 Student s3("Kabeer", "cd345", 0.0,"NULL");
 
  float avg1 = s1.getAvg();
 float avg2 = s2.getAvg();
 float avg3 = s3.getAvg();
 
 stringstream ins1,ins2,ins3;
 ins1<<avg1;
 ins2<<avg2;
ins3<<avg3;
 string Savg1 = ins1.str();
 string Savg2 = ins2.str();
string Savg3 = ins3.str();
 string insert1= "INSERT INTO Student (RollNo,Name,Avg,Grade) VALUES('"+s1.getRollNo()+"','"+s1.getName()+"','"+Savg1+"','"+s1.getGrade()+"')";
string insert2 = "INSERT INTO Student (RollNo,Name,Avg,Grade) VALUES('"+s2.getRollNo()+"', '"+s2.getName()+"','"+Savg2+"', '"+s2.getGrade()+"')";
string insert3 = "INSERT INTO Student (RollNo,Name,Avg,Grade) VALUES('"+s3.getRollNo()+"', '"+s3.getName()+"','"+Savg3+"','"+s3.getGrade()+"')";
if(mysql_query(conn,insert1.c_str()) || mysql_query(conn,insert2.c_str()) || mysql_query(conn,insert3.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
	Sleep(3000);
}
else{
	cout<<"Data Inserted Successfuly."<<endl;
	Sleep(3000);
}

bool exit = false;
while(!exit){
system("cls");
cout<<endl;
cout << "Welcome To Student Report Card System" << endl;
cout << "*************************************" << endl;
cout << "1. Report Card." << endl;
cout << "2. Exit." << endl;
cout << "Enter Your Choice: ";
 int val;
 cin >> val;
 
 if(val==1){
 	system("cls");
 report(conn);	
 Sleep(5000);
 }
else if(val==2){
	exit= true;
	cout<<"Good Luck"<<endl;
	Sleep(3000);
}
else{
	cout<<"Invalid Input"<<endl;
	Sleep(3000);
}
}
mysql_close(conn);
    return 0;
}