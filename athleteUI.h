#ifndef ATHLETEUI_H
#define ATHLETEUI_H
#include "admin.h"
using namespace std;
class AthleteUI :public Admin
{
	static string UserID;
public:
	void SetUserID(string);//获取登录用户ID
	void menu();
	void DisplayProjects();//展示项目信息
	void Applicate();//报名
	void Find_myself();//查询自己报名信息
	void Display_total_college_score();//展示各个学院的团体总分
};
#endif // !ATHLETEUI_H