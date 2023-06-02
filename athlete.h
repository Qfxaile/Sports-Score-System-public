#ifndef ATHLETE_H
#define ATHLETE_H
#include <string>
#include <iostream>
#include "project.h"
#include "college.h"
using namespace std;
class Athlete
{
private:
	string ID;//运动员编号
	string name;//运动员姓名
	bool sex;//性别
	Project pro[5];//一个运动员最多报名5个项目//存放报名的项目以及其分数
	int count_apply;//一个运动员的报名数量
	College col;//运动员所属的学院
public:
	Athlete(string ID = "0", string name = "无", bool sex = 0, string col_ID = "0", string col_name = "无", int count_apply = 0) :col(col_ID, col_name)
	{
		this->ID = ID;
		this->name = name;
		this->sex = sex;
		this->count_apply = count_apply;
	}
	Athlete(const Athlete& at)
	{
		ID = at.ID;
		name = at.name;
		sex = at.sex;
		for (int i = 0; i < at.count_apply; i++)
		{
			pro[i] = at.pro[i];
		}
		col = at.col;
		count_apply = at.count_apply;
	}
	void SetID(string ID) { this->ID = ID; }
	void SetName(string name) { this->name = name; }
	void SetSex(bool sex) { this->sex = sex; }
	void SetCollege(string col_name) { col.SetName(col_name); }//设置运动员的学院
	void SetCount(int count) { count_apply = count; }//设置报名的个数
	string GetID() { return ID; }
	string GetName() { return name; }
	bool GetSex() { return sex; }
	string GetCollege() { return col.GetName(); }//获取运动员所属学院
	int GetCount() { return count_apply; }//获取报名的个数

	Project GetProject(int n) { return pro[n]; }
	void SetStrScore(string pro_name, string score)
	{
		pro[FindProject_ath(pro_name)].SetStrScore(score);
	}
	void SetScore(string pro_name, float score)
	{
		pro[FindProject_ath(pro_name)].SetScore(score);
	}
	string GetStrScore(string pro_name)
	{
		return pro[FindProject_ath(pro_name)].GetStrScore();
	}
	float GetScore(string pro_name)
	{
		return pro[FindProject_ath(pro_name)].GetScore();
	}
	void AddProject(string pro_ID,string pro_name)//添加报名项目
	{
		pro[count_apply].SetID(pro_ID);
		pro[count_apply].SetName(pro_name);
		count_apply++;
	}
	int FindProject_ath(string pro_name)//寻找报名项目信息
	{
		for (int i = 0; i < count_apply; i++)
			if (pro[i].GetName() == pro_name)
				return i;
		return -1;
	}

	friend ostream& operator<<(ostream& os, const Athlete& at)
	{
		os << at.ID << "\t" << at.name << "\t" << (at.sex == 0 ? "女" : "男");
		return os;
	}
	friend istream& operator>>(istream& is, Athlete& at)
	{
		is >> at.ID >> at.name;
		string sex2;
		is >> sex2;
		sex2 == "男" ? (at.sex = 1) : (at.sex = 0);
		return is;
	}
};
#endif // !ATHLETE_H