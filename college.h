#ifndef COLLEGE_H
#define COLLEGE_H
#include <string>
#include <iostream>
using namespace std;
class College//学院类
{
private:
	string ID;//学院编号
	string name;//学院名称
public:
	College(string ID = "0", string name = "无")
	{
		this->ID = ID;
		this->name = name;
	}
	College(const College& co)
	{
		ID = co.ID;
		name = co.name;
	}
	void SetID(string ID) { this->ID = ID; }//更改学院ID
	void SetName(string name) { this->name = name; }//更改学院名称
	string GetID() { return ID; }//获取ID
	string GetName() { return name; }//获取学院名称
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
