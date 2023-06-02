#ifndef COLLEGE_H
#define COLLEGE_H
#include <string>
#include <iostream>
using namespace std;
class College//ѧԺ��
{
private:
	string ID;//ѧԺ���
	string name;//ѧԺ����
public:
	College(string ID = "0", string name = "��")
	{
		this->ID = ID;
		this->name = name;
	}
	College(const College& co)
	{
		ID = co.ID;
		name = co.name;
	}
	void SetID(string ID) { this->ID = ID; }//����ѧԺID
	void SetName(string name) { this->name = name; }//����ѧԺ����
	string GetID() { return ID; }//��ȡID
	string GetName() { return name; }//��ȡѧԺ����
	friend ostream& operator<<(ostream& os, const College& co)
	{
		os << co.ID << "\t\t" << co.name;
		return os;
	}
	friend istream& operator>>(istream& is, College& co)
	{
		is >> co.ID >> co.name;
		return is;
	}
};
#endif // !COLLEGE_H
