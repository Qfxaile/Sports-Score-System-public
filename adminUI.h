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
	void information();//信息处理
	void generate_name_list();//生成报名表
	void maintain_menu();
	void enrollScore();//登记成绩
	void generate_Match_list();//产生比赛名单
	void calculateScore(string);//计分
	//统计
	void statistic_menu();
	void statistic();
	void Statistic_total_college_score();//统计学院总分
	void sort_college_score();//按学院总分排序
	void sort_score(bool);//按男女生团体总分排序//0女 1男
	void sort_project_list();//查看项目前几名的名单
};
#endif // !ADMINUI_H