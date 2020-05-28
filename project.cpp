#include <iostream>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#define s6 "\t\t\t\t\t\t"
#define s5 "\t\t\t\t\t"
#define s4 "\t\t\t\t"
#define s3 "\t\t\t"
#define s2 "\t\t"
#define s1 "\t"
#define sp2 "  "
#define nl endl
#define cyp "Choose your option : "
using namespace std;
void recover(char* , char*);
float getSal(string );
int hashed(char , char, int);
class Employee
{
	public :
	string name, ssn, sal, age, exp, casual, sick, study, parental, sdate, edate, days;
	Employee(){
		casual="20",sick="15",study="10",parental="40",sdate="-",edate="-",days="0";
	}
	void deleteLeave();
	void searchLeave();
	void modLeave();
	void dispLeave();
	void addUser();
	void modUser();
};

void addUser()
{
	Employee e;
	cout<<s4<<"Enter the ID : ";
	cin>>e.ssn;
	e.ssn.resize(8);
	cout<<s4<<"Enter the Name : ";
	cin>>e.name;
	e.name.resize(8);
	cout<<s4<<"Enter the Age : ";
	cin>>e.age;
	e.age.resize(8);
	cout<<s4<<"Enter the Salary : ";
	cin>>e.sal;
	e.sal.resize(8);
	cout<<s4<<"Enther the Experience : ";
	cin>>e.exp;
	e.exp.resize(8);
	fstream file1,file2,file3;
	file1.open("emp.txt",ios::binary|ios::app);
	file2.open("leave.txt",ios::binary|ios::app);
	file3.open("salary.txt",ios::binary|ios::app);
	if(!file1||!file2){
		cout<<s4<<"Error Occured!"<<nl;
		return;
	}
	e.casual=e.casual+"/20-0",e.sick=e.sick+"/15-0",e.study=e.study+"/10-0",e.parental=e.parental+"/40-0";
	e.casual.resize(10),e.sick.resize(10),e.study.resize(10),e.parental.resize(10),e.sdate.resize(10),e.edate.resize(10),e.days.resize(5);
	file1<<s4<<"|"<<e.ssn<<"|"<<e.name<<"|"<<e.age<<"|"<<e.sal<<"|"<<e.exp<<"|"<<nl;
	file2<<e.ssn<<"|"<<e.name<<"|"<<e.casual<<"|"<<e.sick<<"|"<<e.study<<"|"<<e.parental<<"|"<<e.sal<<"|"<<e.sdate<<"|"<<e.edate<<"|"<<e.days<<"|"<<nl;
	file3<<e.ssn<<"|"<<e.sal<<"|"<<nl;
	file1.close();
	file2.close();
	file3.close();
	int index = hashed(e.ssn[0],e.ssn[1],1);

	cout<<s4<<"User added successfully!"<<nl<<nl<<nl;
}
int hashed(char ch1, char ch2, int n)
{
	fstream file1;
	cout<<s4;
	for(int i=0;i<50;i++){
		cout<<".";
	}
	if(n==1)
	cout<<"Storing data at hash index "<<(ch1 + ch2)%100;
	else
		cout<<"Retrieving data from hash index "<<(ch1 + ch2)%100;
	
	for(int i=0;i<50;i++){
		cout<<".";
	}
	cout<<endl;
	return (ch1+ch2)%100;
}
void modUser()
{
	char ch;
	string id,str;
	int found=0,count=0;
	fstream file1,file2;
	file1.open("emp.txt",ios::binary|ios::in);
	cout<<s4<<"Enter the Employee ID to modify : ";
	cin>>id;
	id.resize(8);
	if(!file1){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=5;
	while(file1){
		file1.seekg(index, ios::beg);
		getline(file1,str,'|');
		
		if(str==id){
			found=1;
			break;
	    }
		else{
			index+=51;
			str.clear();
			count++;
		}
	}
	file1.close();
	if(found==1)
	{
		start:
		int ch,beg,end;
		string newstr,str;
		cout<<s4<<"1. EDIT AGE"<<nl;
		cout<<s4<<"2. EDIT SALARY"<<nl;
		cout<<s4<<"3. EDIT EXPERIENCE"<<nl<<nl;
		cout<<s4<<cyp;
		cin>>ch;
		cout<<nl;
		if(ch==1 || ch==2 || ch==3){
			cout<<s4<<"Enter the new value : ";
			cin>>newstr;
		}
		else
			goto start;
		newstr.resize(8);
	
		file1.open("emp.txt",ios::binary|ios::in);
		file2.open("temp.txt",ios::binary|ios::app);

		while(count--){
		getline(file1,str);
		file2<<str<<endl;
	    }
	    if(ch==1)
	    beg=3,end=2;
		else if(ch==2)
		beg=4,end=1;
		else if(ch==3)
		beg=5,end=0;
	    for(int i=0;i<beg;i++){
	    	getline(file1,str,'|');
	    	file2<<str<<"|";
	    }

	    file2<<newstr<<"|";
	    getline(file1,str,'|');
	    for(int i=0;i<end;i++){
	    	getline(file1,str,'|');
	    	file2<<str<<"|";
	    }

	    while(file1){
	    	getline(file1,str);
	    	file2<<str;
	    	if(file1)
	    	file2<<endl;
	    }
	    file1.close();
	    file2.close();
	    cout<<s4<<"Employee has been updated!"<<nl<<nl;
	    char fn1[]="emp.txt",fn2[]="temp.txt";
	   	recover(fn1,fn2);
		   
		
	}
	else
		cout<<s4<<"Employee not found!"<<nl<<nl;

}
void recover(char *fn1,char *fn2)
{
	remove(fn1);
	rename(fn2,fn1);
}

void displayUsers()
{
	string str;
	fstream file;
	file.open("emp.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	cout<<nl<<s4<<"Employee ID"<<s2<<"Name"<<s2<<"Age"<<s2<<"Salary"<<s1<<sp2<<"Experience"<<nl<<nl;
	while(file){
		getline(file,str,'|');
		cout<<str<<s1;
	}
	file.close();
	int t=110;
	cout<<nl<<s3;
	while(t--)
		cout<<"-";
	cout<<nl<<nl;
	file.close();
}

void modLeave()
{
	string id,str;
	int found=0,count=0;
	fstream file1,file2;
	file1.open("leave.txt",ios::binary|ios::in);
	cout<<s4<<"Enter the Employee ID : ";
	cin>>id;
	id.resize(8);
	if(!file1){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=0;
	while(file1){
		file1.seekg(index, ios::beg);
		getline(file1,str,'|');
		if(str==id){
			found=1;
			break;
		}
		else{
			index+=100;
			str.clear();
			count++;
		}
	}
	file1.close();
	if(found==1)
	{
		start:
		string sdate,edate;
		int ch,com=7,beg,end,nol,ex=0,lea,tot,days=0,leave,nod;
		float sal,per;
		cout<<s4<<"1. CASUAL LEAVE"<<nl;
		cout<<s4<<"2. SICK LEAVE"<<nl;
		cout<<s4<<"3. STUDY LEAVE"<<nl;
		cout<<s4<<"4. PARENTAL LEAVE"<<nl<<nl;
		cout<<s4<<cyp;
		cin>>ch;
		if(ch==0 || ch>4)
			goto start;
		cout<<nl;
		if(ch==1){ beg=0,end=3,tot=20,per=0.025; }
		else if(ch==2){ beg=1,end=2,tot=15,per=0.025;}
		else if(ch==3){ beg=2,end=1,tot=10,per=0.025;}
		else if(ch==4){ beg=3,end=0,tot=40,per=0.025;}
		file1.open("leave.txt",ios::binary|ios::in);
		file2.open("temp1.txt",ios::binary|ios::app);
		while(count--){
			getline(file1,str);
			file2<<str<<endl;
		}
		for(int i=0;i<2;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		for(int i=0;i<beg;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		cout<<s4<<"Enter the number of leaves : ";
		cin>>nol;
		while(nol>tot){
			cout<<s4<<"Cannot apply more than "<<tot<<" leaves"<<nl;
			cout<<s4<<"Enter the number of leaves : ";
			cin>>nol;
		}
		getline(file1,str,'|');
		stringstream buf1(str);
		buf1>>lea;
		leave=lea;
		if(lea-nol<0)
		days=abs(lea-nol);
		lea=lea-nol;
		if(days!=0)
		lea=0;
		fstream buf2;
		buf2.open("mod.txt",ios::binary|ios::out);
		buf2<<lea<<"/"<<tot<<"-"<<days;
		buf2.close();
		buf2.open("mod.txt",ios::binary|ios::in);
		getline(buf2,str);
		buf2.close();
		remove("mod.txt");
		str.resize(10);
		file2<<str<<"|";
		for(int i=0;i<end;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		getline(file1,str,'|');
		sal=getSal(id);

		if(leave-nol<0)
		sal-=(float)sal*per*abs(leave-nol);
		
		ostringstream buf4;
		buf4<<sal;
		str=buf4.str();
		str.resize(8);
		file2<<str<<"|";

		cout<<s4<<"Enter the Start Date(dd/mm/yyyy) : ";
		cin>>sdate;
		cout<<s4<<"Enter the End Date(dd/mm/yyy) : ";
		cin>>edate;
		sdate.resize(10);
		edate.resize(10);
		file2<<sdate<<"|";
		file2<<edate<<"|";
		for(int i=0;i<3;i++)
		getline(file1,str,'|');

		stringstream buf5(str);
		buf5>>nod;
		nod=nod+nol;

		ostringstream buf6;
		buf6<<nod;
		str=buf6.str();
		str.resize(5);
		file2<<str<<"|";

		while(file1){
			getline(file1,str);
			file2<<str;
			if(file1)
			file2<<endl;
		}
		file1.close();
		file2.close();
		char fn1[]="leave.txt",fn2[]="temp1.txt";
		recover(fn1,fn2);
		cout<<s4<<"Leave updated!"<<nl<<nl;
	}
	else
		cout<<s4<<"User not found!"<<nl<<nl;
}	

void dispLeave()
{
	string str;
	fstream file;
	file.open("leave.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	cout<<nl<<"Employee ID\t"<<"Name\t\t"<<"CL(20)\t\t"<<"SL(15)\t\t"<<"STL(10)\t\t"<<"PL(40)\t\t"<<"Salary\t\t"<<"Start Date"<<sp2<<sp2<<"End Date"<<sp2<<sp2<<"NoofLeaves"<<nl<<nl;
	while(file){
		getline(file,str,'|');
		cout<<str<<"\t";
	}
	cout<<nl<<nl;
	cout<<"Note : This table shows remaining leaves."<<nl<<sp2<<"CL : CASUAL LEAVE"<<nl<<sp2<<"SL : SICK LEAVESEAVE"<<nl<<sp2<<"STL : STUDY LEAVE"<<nl<<sp2<<"PL : PARENTAL LEAVE"<<nl<<sp2<<"Number after '-' sign indicates extra leaves."<<nl<<nl;
	file.close();
}

void deleteLeave()
{
	string id,str;
	int found=0,count=0;
	fstream file1,file2;
	file1.open("leave.txt",ios::binary|ios::in);
	cout<<s4<<"Enter the Employee ID to delete : ";
	cin>>id;
	id.resize(8);
	if(!file1){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=0;
	while(file1){
		file1.seekg(index,ios::beg);
		getline(file1,str,'|');
		if(str==id){
			found=1;
			break;
		}
		else{
			index+=100;
			str.clear();
			count++;
		}
	}
	file1.close();
	if(found==1)
	{
		file1.open("leave.txt",ios::binary|ios::in);
		file2.open("temp1.txt",ios::binary|ios::app);
		while(count--){
			getline(file1,str);
			file2<<str<<endl;
		}
		for(int i=0;i<2;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		str="20/20-0";str.resize(10);
		file2<<str<<"|";
		str="15/15-0";str.resize(10);
		file2<<str<<"|";
		str="10/10-0";str.resize(10);
		file2<<str<<"|";
		str="40/40-0";str.resize(10);
		file2<<str<<"|";
		float sal=getSal(id);
		ostringstream buf;
		buf<<sal;
		str=buf.str();
		str.resize(8);
		file2<<str<<"|";
		str="-";str.resize(10);
		file2<<str<<"|"<<str<<"|";
		str="0";str.resize(5);
		file2<<str<<"|";
		for(int i=0;i<8;i++)
			getline(file1,str,'|');
		while(file1){
			getline(file1,str);
			file2<<str;
			if(file1)
			file2<<endl;
		}
		file1.close();
		file2.close();
		char fn1[]="leave.txt",fn2[]="temp1.txt";
		recover(fn1,fn2);
	}
	else
		cout<<s4<<"User not found!"<<nl;
}

float getSal(string id)
{
	fstream file;
	float sal;
	string str;
	file.open("salary.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return 0;
	}
	int index=0;
	while(file){
		file.seekg(index,ios::beg);
		getline(file,str,'|');
		str.resize(8);
		if(str==id){
			break;
		}
		else{
			index+=19;
			str.clear();
		}
	}
	str.clear();
	getline(file,str,'|');
	stringstream buf(str);
	buf>>sal;
	file.close();
	return sal;
}
void searchLeave()
{
	string id,str;
	cout<<s4<<"Enter the Employee ID : ";
	cin>>id;
	id.resize(8);
	fstream file;
	file.open("leave.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=0;
	while(file){
		file.seekg(index,ios::beg);
		getline(file,str,'|');
		str.resize(8);
		if(str==id){
			break;
		}
		else{
			index+=100;
			str.clear();
		}
	}
	int hash = hashed(id[0], id[1], 0);
	cout<<nl<<"Employee ID\t"<<"Name\t\t"<<"CL(20)\t\t"<<"SL(15)\t\t"<<"STL(10)\t\t"<<"PL(40)\t\t"<<"Salary\t\t"<<"Start Date"<<sp2<<sp2<<"End Date"<<sp2<<sp2<<"NoofLeaves"<<nl<<nl;
	cout<<str<<"\t";
	for(int i=0;i<9;i++){
		getline(file,str,'|');
		cout<<str<<"\t";
	}
	file.close();
	cout<<nl<<nl;
}
int main()
{
	while(true){
	start:
	int ch;
	cout<<s3<<"----- E M P L O Y E E   L E A V E   M A N A G E M E N T  S Y S T E M -----"<<nl<<nl;
	cout<<s6<<"--- M A I N  M E N U ---"<<nl<<nl;
	cout<<s4<<"1. APPLY LEAVE"<<nl;
	cout<<s4<<"2. DELETE LEAVE"<<nl;
	cout<<s4<<"3. SEARCH LEAVE"<<nl;
	cout<<s4<<"4. MODIFY LEAVE"<<nl;
	cout<<s4<<"5. DISPLAY ALL LEAVES"<<nl;
	cout<<s4<<"6. USER MANAGEMENT"<<nl;
	cout<<s4<<"7. EXIT"<<nl;
	cout<<nl<<s4<<cyp;
	cin>>ch;
	cout<<nl;
	switch(ch)
	{
		case 1:
			modLeave();
			break;
		case 2:
			deleteLeave();
			break;
		case 3:
			searchLeave();
			break;
		case 4:
			modLeave();
			break;
		case 5:
		 	dispLeave();
		 	break;
		case 6:
			int ch1;
			cout<<s4<<"1. ADD USER"<<nl<<s4<<"2. MODIFY USER"<<nl;
			cout<<s4<<"3. DISPLAY ALL USERS INFORMATION"<<nl;
			cout<<nl<<s4<<cyp;
			cin>>ch1;
			cout<<nl;
			if(ch1==1)
			addUser();
			else if(ch1==2)
			modUser();
			else if(ch1==3)
			displayUsers();
			break;

		case 7:
			exit(0);

		default : goto start;
	 }
	}
	return 0;
}
