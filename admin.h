#ifndef ADMIN_H
#define ADMIN_H
#include "college.h"
#include "project.h"
#include "athlete.h"
using namespace std;
class Admin
{
protected:
	int c, p, a;//各个数据的数量
	College col[6];//最多6学院
	Project pro[6];//6项目
	Athlete ath[50];//50运动员
	static int A;//同系最大报名人数
	static int B;//全部人数
public:
	Admin();
	~Admin();
	void enter_end();//按下回车键才结束
	//展示信息
	void ShowCollege();
	void ShowProject();
	void ShowAthlete();
	//信息添加
	void AddCollege();
	void AddProject();
	void AddAthlete();
	//信息删除
	void RemoveCollege();
	void RemoveProject();
	void RemoveAthlete();
	//信息修改
	void SetCollege();
	void SetProject();
	void SetAthlete();
	//信息查询
	//ID false / Name true
	int FindCollege(string);
	int FindProject(string);
	int FindAthlete(string);
	void FindCollege();
	void FindProject();
	void FindAthlete();
	//信息保存//全部信息保存
	void SaveCollege();
	void SaveProject();
	void SaveAthlete();
	void Save_apply_score();//保存报名与分数信息(报名时，分数默认为0)
	//信息读取
	void ReadCollege();
	void ReadProject();
	void ReadAthlete();
	void ReadApply();
	//排序
	void Sort_by_ID(College[]);
	void Sort_by_ID(Project[]);
	void Sort_by_ID(Athlete[]);
	//人数
	int count_Athlete_sex(string, bool);//0 女 /1 男
	int count_Athlete_college(string, string);//同系报名人数//项目/专业
	int count_Athlete(string);//整个项目报名人数
	float sum_score(string);//学院名//计算某学院的总分
	friend bool compare_ID_col(College& a, College& b);
	friend bool compare_ID_pro(Project& a, Project& b);
	friend bool compare_ID_ath(Athlete& a, Athlete& b);
};
#endif // !ADMIN_H