#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include<string>
#include<map>
 using namespace std;
 extern map<string,string> userpass;
 extern bool processed;
 extern string auth_user;
 bool isLoggedIn();
 void init();


#endif // LOGIN_H_INCLUDED
