#ifndef ATHLETEUI_H
#define ATHLETEUI_H
#include "admin.h"
using namespace std;
class AthleteUI :public Admin
{
	static string UserID;
public:
	void SetUserID(string);//��ȡ��¼�û�ID
	void menu();
	void DisplayProjects();//չʾ��Ŀ��Ϣ
	void Applicate();//����
	void Find_myself();//��ѯ�Լ�������Ϣ
	void Display_total_college_score();//չʾ����ѧԺ�������ܷ�
};
#endif // !ATHLETEUI_H