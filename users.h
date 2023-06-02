#ifndef USERS_H
#define USERS_H
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Users
{
private:
	string name;//用户名称
	string user;//账号
	string password;//密码
    bool GM;//判断是否为管理员
public:
    Users(string name = "", string user = "", string password = "");

    void SetName(string name) { this->name = name; }
    void SetUser(string user) { this->user = user; }
    void SetPassword(string password) { this->password = password; }
    void SetGM(bool GM) { this->GM = GM; }
    string GetName() { return name; }
    string GetUser() { return user; }
    string GetPassword() { return password; }
    bool GetGM() { return GM; }

    void Set(string name, string user, string password, bool GM);
    friend ostream& operator<<(ostream& os, Users& user);
    friend istream& operator>>(istream& is, Users& user);
};
#endif // !USERS_H