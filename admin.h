#ifndef ADMIN_H
#define ADMIN_H
#include "college.h"
#include "project.h"
#include "athlete.h"
using namespace std;
class Admin
{
protected:
	int c, p, a;//�������ݵ�����
	College col[6];//���6ѧԺ
	Project pro[6];//6��Ŀ
	Athlete ath[50];//50�˶�Ա
	static int A;//ͬϵ���������
	static int B;//ȫ������
public:
	Admin();
	~Admin();
	void enter_end();//���»س����Ž���
	//չʾ��Ϣ
	void ShowCollege();
	void ShowProject();
	void ShowAthlete();
	//��Ϣ���
	void AddCollege();
	void AddProject();
	void AddAthlete();
	//��Ϣɾ��
	void RemoveCollege();
	void RemoveProject();
	void RemoveAthlete();
	//��Ϣ�޸�
	void SetCollege();
	void SetProject();
	void SetAthlete();
	//��Ϣ��ѯ
	//ID false / Name true
	int FindCollege(string);
	int FindProject(string);
	int FindAthlete(string);
	void FindCollege();
	void FindProject();
	void FindAthlete();
	//��Ϣ����//ȫ����Ϣ����
	void SaveCollege();
	void SaveProject();
	void SaveAthlete();
	void Save_apply_score();//���汨���������Ϣ(����ʱ������Ĭ��Ϊ0)
	//��Ϣ��ȡ
	void ReadCollege();
	void ReadProject();
	void ReadAthlete();
	void ReadApply();
	//����
	void Sort_by_ID(College[]);
	void Sort_by_ID(Project[]);
	void Sort_by_ID(Athlete[]);
	//����
	int count_Athlete_sex(string, bool);//0 Ů /1 ��
	int count_Athlete_college(string, string);//ͬϵ��������//��Ŀ/רҵ
	int count_Athlete(string);//������Ŀ��������
	float sum_score(string);//ѧԺ��//����ĳѧԺ���ܷ�
	friend bool compare_ID_col(College& a, College& b);
	friend bool compare_ID_pro(Project& a, Project& b);
	friend bool compare_ID_ath(Athlete& a, Athlete& b);
};
#endif // !ADMIN_H