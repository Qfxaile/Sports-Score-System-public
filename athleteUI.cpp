#include "athleteUI.h"
#include <fstream>
#include "io.h"//_access()
#include <iostream>
using namespace std;
string AthleteUI::UserID = "2116220000";//Ĭ��ֵ
void AthleteUI::SetUserID(string ID)//��ȡ��¼�û�ID
{
	UserID = ID;
}
void AthleteUI::menu()
{
	cout << "###��ӭ�����˶�Աҳ��###" << endl;
	cout << "(1)	��ȡ��Ŀ��Ϣ" << endl;
	cout << "(2)	����" << endl;
	cout << "(3)	��ѯ��Ϣ" << endl;
	cout << "(4)	�鿴ѧԺ�ܷ�" << endl;
	cout << "(5)	�˳���¼" << endl;
	cout << "(6)	�˳�ϵͳ" << endl;
	cout << "��ѡ��";
}
void AthleteUI::DisplayProjects()//չʾ��Ŀ��Ϣ
{
	if (FindAthlete(UserID) == -1)
	{
		cout << "���ȱ�����" << endl;
		enter_end();
		return;
	}
	cout << "###������Ŀ��Ϣ###" << endl;
	cout << "ID\t\t��Ŀ��\t\t����ʱ��\t\t����\tŮ��\tͬϵ\t�ܹ�" << endl;
	for (int i = 0; i < p; i++)
	{
		cout << pro[i] << "\t\t" << pro[i].GetTime() << '\t';
		string pro_name = pro[i].GetName();
		cout << count_Athlete_sex(pro_name, true) << '\t' << count_Athlete_sex(pro_name, false) << '\t';
		cout << count_Athlete_college(pro_name, ath[FindAthlete(UserID)].GetCollege()) << '/' << A << '\t';
		int sum = count_Athlete_sex(pro_name, true) + count_Athlete_sex(pro_name, false);
		cout << sum << '/' << B;
		cout << endl;
	}
	enter_end();
}
void AthleteUI::Applicate()//����
{
	cout << "����ǰ��ѧ��/����Ϊ��" << UserID << endl;
	string col_ID, pro_ID, name, sex;
	if (FindAthlete(UserID) == -1)//û�ҵ����˶�Ա�Ż�������Ӧ��Ϣ
	{
		ShowCollege();
		cout << "�����������ڵ�ѧԺID��";
		cin >> col_ID;
		cout << "����������������";
		cin >> name;
		cout << "�����������Ա�(��/Ů)��";
		cin >> sex;
		//д����Ϣ
		ath[a].SetID(UserID);
		ath[a].SetName(name);
		ath[a].SetSex((sex == "��" ? 1 : 0));
		ath[a].SetCollege(col[FindCollege(col_ID)].GetName());
		a++;
	}
	else
		col_ID = col[FindCollege(ath[FindAthlete(UserID)].GetCollege())].GetID();//���ѧԺID

	ShowProject();
	cout << "��������Ҫ��������ĿID(�˳���������-1)��";
	cin >> pro_ID;
	if (pro_ID == "-1")//�˳�����
	{
		system("cls");
		return;
	}
	if (FindProject(pro_ID) != -1)//�ҵ���
	{
		//�жϱ��������Ƿ񳬳�
		if (count_Athlete_college(pro[FindProject(pro_ID)].GetName(),
			col[FindCollege(col_ID)].GetName()) >= A//ͬϵ��������
			||
			count_Athlete(pro[FindProject(pro_ID)].GetName()) >= B//��Ŀ������
			)
		{
			cout << "�������ɱ������������ɱ�����" << endl;
			enter_end();
			return;
		}

		//�ж��Ƿ��ظ�����
		int ID_count = ath[FindAthlete(UserID)].GetCount();//��ȡ�û��ı�������
		if (ID_count > 0 && ath[FindAthlete(UserID)].FindProject_ath(pro[FindProject(pro_ID)].GetName()) != -1)//��Ŀ�Ѿ����û��д��ڣ�˵����������
		{
			cout << "�����ظ�����ͬһ��������������룡" << endl;
			enter_end();
			Applicate();
			return;
		}

		//û���ظ�����
		cout << "��ȷ����Ҫ��������ĿΪ��" << pro[FindProject(pro_ID)].GetName() << endl;
		ath[FindAthlete(UserID)].AddProject(pro_ID, pro[FindProject(pro_ID)].GetName());
		ath[FindAthlete(UserID)].SetScore(pro[FindProject(pro_ID)].GetName(), 0);//������ʱ��Ĭ��ֵΪ0
		ath[FindAthlete(UserID)].SetStrScore(pro[FindProject(pro_ID)].GetName(), "0000");//�ɼ�����Ϊ0
		Save_apply_score();
		cout << "�����ɹ���" << endl;
	}
	else
		cout << "û���ҵ�����Ŀ��" << endl;
	enter_end();
}
void AthleteUI::Find_myself()//��ѯ�Լ�������Ϣ
{
	int n = FindAthlete(UserID);
	if (n == -1)
	{
		cout << "�����������û�" << UserID << "���˶�Ա��Ϣ�����ȱ�����" << endl;
		enter_end();
		return;
	}
	cout << "###������Ϣ###" << endl;
	cout << "������\t����" << ath[n].GetName() << endl;
	cout << "�Ա�\t����" << (ath[n].GetSex() == 0 ? "Ů" : "��") << endl;
	cout << "ѧ��/���ţ�" << UserID << endl;
	cout << "ѧԺ��\t����" << ath[n].GetCollege() << endl;
	cout << "�ѱ�����Ŀ��" << endl;
	if (ath[n].GetCount() > 0)//���ڱ�����Ϣ
	{
		cout << "���\t��Ŀ��\t����ʱ��\t\tͬϵ\t�ܹ�\t�ɼ�\t�÷�" << endl;
		int count = 0;//���
		for (int i = 0; i < ath[n].GetCount(); i++)
		{
			count++;//���������ţ�������ID��
			Project temp = pro[FindProject(ath[n].GetProject(i).GetID())];//���캯����ʼ��//��ȡ��Ŀ
			cout << count << '\t' << temp.GetName() << "\t" << temp.GetTime() << '\t';
			string pro_name = temp.GetName();
			cout << count_Athlete_college(pro_name, ath[FindAthlete(UserID)].GetCollege()) << '/' << A << '\t';
			int sum = count_Athlete_sex(pro_name, true) + count_Athlete_sex(pro_name, false);
			cout << sum << '/' << B << "\t";
			cout << ath[n].GetProject(i).GetStrScore() << "\t" << ath[n].GetProject(i).GetScore() << endl;
		}
	}
	else
		cout << "�ޱ�����Ŀ��" << endl;
	enter_end();
}
void AthleteUI::Display_total_college_score()//չʾ����ѧԺ�������ܷ�
{
	cout << "###��ѧԺ�����ܷ�###" << endl;
	cout << "ID\t\tѧԺ\t\t�ܷ�" << endl;
	for (int i = 0; i < c; i++)
	{
		cout << col[i] << "\t\t" << sum_score(col[i].GetName()) << endl;
	}
	enter_end();
}