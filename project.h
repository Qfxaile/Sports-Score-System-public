#ifndef PROJECT_H
#define PROJECT_H
#include <string>
#include "date.h"
using namespace std;
class Project
{
private:
	string ID;//��Ŀ���
	string name;//��Ŀ����
	Date Mtime;//����ʱ��//������ʱ��
	string Str_Score;//�����ɼ�
	float Score;//�����÷�
public:
	Project(string ID = "0", string name = "��", int y = 1970, int m = 1, int d = 1, int h = 0, int min = 0, string Str_Score = "0000", float Score = 0) :Mtime(y, m, d, h, min)
	{
		this->ID = ID;
		this->name = name;
		this->Str_Score = Str_Score;
		this->Score = Score;
	}
	Project(const Project& pr)
	{
		ID = pr.ID;
		name = pr.name;
		Mtime = pr.Mtime;
		Str_Score = pr.Str_Score;
		Score = pr.Score;
	}
	void SetID(string ID) { this->ID = ID; }//������ĿID
	void SetName(string name) { this->name = name; }//������Ŀ����
	void SetTime(Date date) { this->Mtime = date; }
	void SetStrScore(string Str_Score) { this->Str_Score = Str_Score; }
	void SetScore(float Score) { this->Score = Score; }
	string GetID() { return ID; }//��ȡ��ĿID
	string GetName() { return name; }//��ȡ��Ŀ����
	Date GetTime() { return Mtime; }
	string GetStrScore() { return Str_Score; }
	float GetScore() { return Score; }
	friend ostream& operator<<(ostream& os, const Project& pr)
	{
		os << pr.ID << "\t\t" << pr.name;
		return os;
	}
	friend istream& operator>>(istream& is, Project& pr)
	{
		is >> pr.ID >> pr.name;
		return is;
	}
};
#endif // !PROJECT_H