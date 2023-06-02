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
	string ID;//�˶�Ա���
	string name;//�˶�Ա����
	bool sex;//�Ա�
	Project pro[5];//һ���˶�Ա��౨��5����Ŀ//��ű�������Ŀ�Լ������
	int count_apply;//һ���˶�Ա�ı�������
	College col;//�˶�Ա������ѧԺ
public:
	Athlete(string ID = "0", string name = "��", bool sex = 0, string col_ID = "0", string col_name = "��", int count_apply = 0) :col(col_ID, col_name)
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
	void SetCollege(string col_name) { col.SetName(col_name); }//�����˶�Ա��ѧԺ
	void SetCount(int count) { count_apply = count; }//���ñ����ĸ���
	string GetID() { return ID; }
	string GetName() { return name; }
	bool GetSex() { return sex; }
	string GetCollege() { return col.GetName(); }//��ȡ�˶�Ա����ѧԺ
	int GetCount() { return count_apply; }//��ȡ�����ĸ���

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
	void AddProject(string pro_ID,string pro_name)//��ӱ�����Ŀ
	{
		pro[count_apply].SetID(pro_ID);
		pro[count_apply].SetName(pro_name);
		count_apply++;
	}
	int FindProject_ath(string pro_name)//Ѱ�ұ�����Ŀ��Ϣ
	{
		for (int i = 0; i < count_apply; i++)
			if (pro[i].GetName() == pro_name)
				return i;
		return -1;
	}

	friend ostream& operator<<(ostream& os, const Athlete& at)
	{
		os << at.ID << "\t" << at.name << "\t" << (at.sex == 0 ? "Ů" : "��");
		return os;
	}
	friend istream& operator>>(istream& is, Athlete& at)
	{
		is >> at.ID >> at.name;
		string sex2;
		is >> sex2;
		sex2 == "��" ? (at.sex = 1) : (at.sex = 0);
		return is;
	}
};
#endif // !ATHLETE_H