#ifndef USERSUI_H
#define USERSUI_H
#include "users.h"
class UsersUI
{
	int c;//用户数量
	Users users[10];
	int GM;//判断是否为管理员
public:
	UsersUI();//用于初始化用户数量
	~UsersUI();//用于结束时自动排序，并且将全部数据存放入文件中
	int GetGM() { return GM; }//返回管理员状态
	string GetID() { return users->GetUser(); }
	void menu();//功能执行
	void main_menu();//主菜单
	void regist_menu();//注册菜单
	void regist(int GM = 0);//注册//true为管理员注册，false为普通用户注册
	void login();//登录//true管理员登录 false为普通用户登录
	bool regist_enterpassword();//注册输入密码
	void login_enterpassword(string user);//登录输入密码//判断是否正确
	int finduser(string user);//找到用户
	bool user_to_password(string user, string password);//判断用户名密码是否匹配
	void sort_by_user();//按照学号/工号大小排序，让文件内容更加整洁
};
#endif // !USERSUI_H
