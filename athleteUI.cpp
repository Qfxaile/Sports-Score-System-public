#include "athleteUI.h"
#include <fstream>
#include "io.h"//_access()
#include <iostream>
using namespace std;
string AthleteUI::UserID = "2116220000";//默认值
void AthleteUI::SetUserID(string ID)//获取登录用户ID
{
	UserID = ID;
}
void AthleteUI::menu()
{
	cout << "###欢迎来到运动员页面###" << endl;
	cout << "(1)	获取项目信息" << endl;
	cout << "(2)	报名" << endl;
	cout << "(3)	查询信息" << endl;
	cout << "(4)	查看学院总分" << endl;
	cout << "(5)	退出登录" << endl;
	cout << "(6)	退出系统" << endl;
	cout << "请选择：";
}
void AthleteUI::DisplayProjects()//展示项目信息
{
	if (FindAthlete(UserID) == -1)
	{
		cout << "请先报名！" << endl;
		enter_end();
		return;
	}
	cout << "###各个项目信息###" << endl;
	cout << "ID\t\t项目名\t\t比赛时间\t\t男生\t女生\t同系\t总共" << endl;
	for (int i = 0; i < p; i++)
	{
		cout << pro[i] << "\t\t" << pro[i].GetTime() << '\t';
		string pro_name = pro[i].GetName();
		cout << count_Athlete_sex(pro_name, true) << '\t' << count_Athlete_sex(pro_name, false) << '\t';
		cout << count_Athlete_college(pro_name, ath[FindAthlete(UserID)].GetCollege()) << '/' << A << '\t';
		int sum = count_Athlete_sex(pro_name, true) + count_Athlete_sex(pro_name, false);
		cout << sum << '/' << B;
		cout << endl;
	}
	enter_end();
}
void AthleteUI::Applicate()//报名
{
	cout << "您当前的学号/工号为：" << UserID << endl;
	string col_ID, pro_ID, name, sex;
	if (FindAthlete(UserID) == -1)//没找到该运动员才会输入相应信息
	{
		ShowCollege();
		cout << "请输入您所在的学院ID：";
		cin >> col_ID;
		cout << "请输入您的姓名：";
		cin >> name;
		cout << "请输入您的性别(男/女)：";
		cin >> sex;
		//写入信息
		ath[a].SetID(UserID);
		ath[a].SetName(name);
		ath[a].SetSex((sex == "男" ? 1 : 0));
		ath[a].SetCollege(col[FindCollege(col_ID)].GetName());
		a++;
	}
	else
		col_ID = col[FindCollege(ath[FindAthlete(UserID)].GetCollege())].GetID();//获得学院ID

	ShowProject();
	cout << "请输入您要报名的项目ID(退出报名输入-1)：";
	cin >> pro_ID;
	if (pro_ID == "-1")//退出报名
	{
		system("cls");
		return;
	}
	if (FindProject(pro_ID) != -1)//找到了
	{
		//判断报名人数是否超出
		if (count_Athlete_college(pro[FindProject(pro_ID)].GetName(),
			col[FindCollege(col_ID)].GetName()) >= A//同系报名人数
			||
			count_Athlete(pro[FindProject(pro_ID)].GetName()) >= B//项目总人数
			)
		{
			cout << "超出最大可报名人数！不可报名！" << endl;
			enter_end();
			return;
		}

		//判断是否重复报名
		int ID_count = ath[FindAthlete(UserID)].GetCount();//获取用户的报名人数
		if (ID_count > 0 && ath[FindAthlete(UserID)].FindProject_ath(pro[FindProject(pro_ID)].GetName()) != -1)//项目已经在用户中存在，说明报过名了
		{
			cout << "不可重复报名同一报名项！请重新输入！" << endl;
			enter_end();
			Applicate();
			return;
		}

		//没有重复报名
		cout << "已确认您要报名的项目为：" << pro[FindProject(pro_ID)].GetName() << endl;
		ath[FindAthlete(UserID)].AddProject(pro_ID, pro[FindProject(pro_ID)].GetName());
		ath[FindAthlete(UserID)].SetScore(pro[FindProject(pro_ID)].GetName(), 0);//报名的时候，默认值为0
		ath[FindAthlete(UserID)].SetStrScore(pro[FindProject(pro_ID)].GetName(), "0000");//成绩表面为0
		Save_apply_score();
		cout << "报名成功！" << endl;
	}
	else
		cout << "没有找到该项目！" << endl;
	enter_end();
}
void AthleteUI::Find_myself()//查询自己报名信息
{
	int n = FindAthlete(UserID);
	if (n == -1)
	{
		cout << "不存在属于用户" << UserID << "的运动员信息，请先报名！" << endl;
		enter_end();
		return;
	}
	cout << "###报名信息###" << endl;
	cout << "姓名：\t——" << ath[n].GetName() << endl;
	cout << "性别：\t——" << (ath[n].GetSex() == 0 ? "女" : "男") << endl;
	cout << "学号/工号：" << UserID << endl;
	cout << "学院：\t——" << ath[n].GetCollege() << endl;
	cout << "已报名项目：" << endl;
	if (ath[n].GetCount() > 0)//存在报名信息
	{
		cout << "序号\t项目名\t比赛时间\t\t同系\t总共\t成绩\t得分" << endl;
		int count = 0;//序号
		for (int i = 0; i < ath[n].GetCount(); i++)
		{
			count++;//用于输出序号（并不是ID）
			Project temp = pro[FindProject(ath[n].GetProject(i).GetID())];//构造函数初始化//获取项目
			cout << count << '\t' << temp.GetName() << "\t" << temp.GetTime() << '\t';
			string pro_name = temp.GetName();
			cout << count_Athlete_college(pro_name, ath[FindAthlete(UserID)].GetCollege()) << '/' << A << '\t';
			int sum = count_Athlete_sex(pro_name, true) + count_Athlete_sex(pro_name, false);
			cout << sum << '/' << B << "\t";
			cout << ath[n].GetProject(i).GetStrScore() << "\t" << ath[n].GetProject(i).GetScore() << endl;
		}
	}
	else
		cout << "无报名项目！" << endl;
	enter_end();
}
void AthleteUI::Display_total_college_score()//展示各个学院的团体总分
{
	cout << "###各学院团体总分###" << endl;
	cout << "ID\t\t学院\t\t总分" << endl;
	for (int i = 0; i < c; i++)
	{
		cout << col[i] << "\t\t" << sum_score(col[i].GetName()) << endl;
	}
	enter_end();
}