#include <iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<map>
#include <sys/stat.h>
#include <sys/types.h>
#include "sha256.h"
#include "Login.h"
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

map<string,string> userpass;
 bool processed;
 string auth_user;
void init()
{
processed=false;
string pathname="ProjectData";
struct stat info;
int statRC = stat( &pathname[0], &info );
if(statRC!=0)
{  cout<<"..\n";
    if (mkdir(&pathname[0], 0777) == -1)
    cerr << "Error in creating directory:  " << endl;
}
        ifstream file;
        file.open("ProjectData/users.csv");
        if (!file) {
            ofstream cfile;
            cfile.open("ProjectData/users.csv");
            cfile.close();
        }
        else
        file.close();

}
 bool isLoggedIn()
{
        ifstream file;
        file.open("ProjectData/users.csv");
        if (!file) {
        cerr << "Unable to access users data \n";
        exit(1);   // call system to stop
        }
        string row;
        while(file>>row&&processed==false)
        {
         string tempuser="",temppass="";
         int j=0;
         for(j=0;j<row.length();j++)
         {
            if(row[j]==',')
             {break;}
             tempuser=tempuser+row[j];
         }
         j=j+1;
         for(;j<row.length();j++)
         {
            if(row[j]=='\n')
             {break;}
             temppass=temppass+row[j];
         }
         userpass.insert(make_pair(tempuser,temppass));
        }
        processed=true;
        file.close();
        //for(auto it=userpass.begin();it!=userpass.end();++it)
        //cout<<it->first<<endl;
    int choice;
    cout<<"\n ---------WELLCOME !!!! ------------\n\n";
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"\n  ~~~~~~~ENTER YOUR CHOICE~~~~~~~    \n";
    cout<<"--------------------\n";
    cout<<"| 1> for register   |\n";
    cout<<"--------------------\n";
    cout<<"| 2> for login      |\n";
    cout<<"--------------------\n";
    cout<<"| 3> for exit       |\n";
    cout<<"---------------------\n";
    cout<<"\n";
    cin>>choice;
    if(choice==1)
    {   cout<<"---------------------------------\n";
        string username,password,retypedpassword;
        cout<<"Type your chosen username : ";cin>>username;
        if(userpass.find(username)!=userpass.end())
        {
            cout<<"Username Already Present !\n";
            return false;
        }
        while(true)
        {   cout<<"-----------------------------\n";
            password=getpass("Enter your chosen password :");
            retypedpassword=getpass("Enter your password again :");
        if(password!=retypedpassword)
        {
        cout<<"Passwords do not match !!!!!!!!! type again \n";
        }
        else
        {
        break;
        }
    }
    ofstream file;
    file.open("ProjectData/users.csv",std::ios_base::app);
    file<<username<<","<<sha256(password)<<endl;
    userpass.insert(make_pair(username,sha256(password)));
    file.close();
    string userdirectory="ProjectData/"+username;
    if (mkdir(&userdirectory[0], 0777) == -1)
        cerr << "Error in creating directory:  " << endl;
    cout<<"Registered successfully ! \n\n";
    cout<<"Write down your username and password somewhere so that you dont forget it\n";
    cout<<"-----------------------------------------\n";
     return false;
    }
    else if(choice==2)
    {
        string username,password;
        cout<<"Enter Login Username : ";cin>>username;
        if(userpass.find(username)==userpass.end())
        {
            cout<<"This username does not exist \n";
            return false;
        }
        password=getpass("Enter the password : ");
        string hashed=sha256(password);
        if(userpass[username]==hashed)
        {
            cout<<"Logged In successfully !\n";
            auth_user=username;
            cout<<"----------------------------------------\n";
            cout<<"-                                      -\n";
            cout<<"-          WELCOME!!                   -\n";
            cout<<"-           BACK!!                     -\n";
            cout<<"-                                      -\n";
            cout<<"----------------------------------------\n";
            return true;
        }
        else
        {
        cout<<"Entered password is WRONG !!!\n";
        return false;
        }
    }
    else{

        _exit(0);
    }

}
