#ifndef ADMINUI_H
#define ADMINUI_H
#include "admin.h"
using namespace std;
class AdminUI :public Admin
{
public:
	void menu();
	void infor_menu();
	void infor2_menu();
	void information();//��Ϣ����
	void generate_name_list();//���ɱ�����
	void maintain_menu();
	void enrollScore();//�Ǽǳɼ�
	void generate_Match_list();//������������
	void calculateScore(string);//�Ʒ�
	//ͳ��
	void statistic_menu();
	void statistic();
	void Statistic_total_college_score();//ͳ��ѧԺ�ܷ�
	void sort_college_score();//��ѧԺ�ܷ�����
	void sort_score(bool);//����Ů�������ܷ�����//0Ů 1��
	void sort_project_list();//�鿴��Ŀǰ����������
};
#endif // !ADMINUI_H