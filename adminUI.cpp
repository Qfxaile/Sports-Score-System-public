#include "adminUI.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
void AdminUI::menu()
{
	cout << "###��ӭ��������Աҳ��###" << endl;
	cout << "(1)	��Ϣ����" << endl;
	cout << "(2)	���ɱ�����" << endl;
	cout << "(3)	�Ǽǳɼ�" << endl;
	cout << "(4)	���ɾ�������" << endl;
	cout << "(5)	ͳ��" << endl;
	cout << "(6)	�˳���¼" << endl;
	cout << "(7)	�˳�ϵͳ" << endl;
	cout << "��ѡ��";
}
void AdminUI::infor_menu()
{
	cout << "###��Ϣ����###" << endl;
	cout << "(1)	ѧԺ��Ϣ" << endl;
	cout << "(2)	��Ŀ��Ϣ" << endl;
	cout << "(3)	�˶�Ա��Ϣ" << endl;
	cout << "(4)	������һҳ" << endl;
	cout << "��ѡ��";
}
void AdminUI::infor2_menu()
{
	cout << "(1)	���" << endl;
	cout << "(2)	�޸�" << endl;
	cout << "(3)	��ѯ" << endl;
	cout << "(4)	ɾ��" << endl;
	cout << "(5)	չʾ��Ϣ" << endl;
	cout << "(6)	������һҳ" << endl;
	cout << "(7)	����������" << endl;
	cout << "��ѡ��";
}
void AdminUI::information()//��Ϣ����
{
	int i;
	for (;;)
	{
		infor_menu();
		cin >> i;
		system("cls");
		switch (i)
		{
		case 1://ѧԺ��Ϣ
		{
			int n;
			for (;;)
			{
				cout << "###ѧԺ��Ϣ###" << endl;
				infor2_menu();
				cin >> n;
				system("cls");
				switch (n)
				{
				case 1:AddCollege(); break;
				case 2:SetCollege(); break;
				case 3:FindCollege(); break;
				case 4:RemoveCollege(); break;
				case 5:ShowCollege();enter_end();break;
				case 6:information(); return;
				case 7:system("cls");return;
				}
				SaveCollege();
			}
			break;
		}
		case 2://��Ŀ��Ϣ
		{
			int n;
			for (;;)
			{
				cout << "###��Ŀ��Ϣ###" << endl;
				infor2_menu();
				cin >> n;
				system("cls");
				switch (n)
				{
				case 1:AddProject(); break;
				case 2:SetProject(); break;
				case 3:FindProject(); break;
				case 4:RemoveProject(); break;
				case 5:ShowProject();enter_end();break;
				case 6:information(); return;
				case 7:system("cls");return;
				}
				SaveProject();
			}
			break;
		}
		case 3://�˶�Ա��Ϣ
		{
			int n;
			for (;;)
			{
				cout << "###�˶�Ա��Ϣ###" << endl;
				infor2_menu();
				cin >> n;
				system("cls");
				switch (n)
				{
				case 1:AddAthlete(); break;
				case 2:SetAthlete(); break;
				case 3:FindAthlete(); break;
				case 4:RemoveAthlete(); break;
				case 5:ShowAthlete();enter_end();break;
				case 6:information(); return;
				case 7:system("cls");return;
				}
				SaveAthlete();
			}
			break;
		}
		case 4:system("cls");return;//������һҳ
		default:
		{
			cout << "��������������������룡" << endl;
			enter_end();
			information();
			return;
		}
		}
	}
}
void AdminUI::generate_name_list()//���ɱ�����
{
	cout << "�������ɱ���������" << endl;
	ofstream ofile;
	ofile.open("sports_score_system/������.txt");
	ofile << "������Ϣ";
	for (int i = 0; i < p; i++)//��Ŀ
	{
		if (count_Athlete(pro[i].GetName()) == 0)//��ȡͬ��Ŀ��������
			continue;
		ofile << endl << "(" << pro[i].GetID() << ")" << pro[i].GetName() << "��";
		for (int j = 0; j < a; j++)//�ҳ����������Ŀƥ��ı���userID
		{
			if (ath[j].FindProject_ath(pro[i].GetName())!=-1)//���˶�Ա������Ŀ���ҵ�
			{
				ofile << endl << ath[j].GetID() << "\t" << ath[j].GetName();
			}
		}
	}
	ofile.close();
	cout << "�ѱ�������ǰĿ¼�µ� ������.txt ��" << endl;
	enter_end();
}
void AdminUI::maintain_menu()
{
	cout << "###ά��������###" << endl;
	cout << "(1)	���" << endl;
	cout << "(2)	ɾ��" << endl;
	cout << "(3)	�޸�" << endl;
	cout << "(4)	����" << endl;
	cout << "(5)	������һҳ" << endl;
	cout << "��ѡ��";
}
void AdminUI::enrollScore()//�Ǽǳɼ�
{
	ShowAthlete();
	cout << "��������Ҫ�Ǽǳɼ����˶�Ա��ID��";
	string At_ID;
	cin >> At_ID;
	Athlete temp = ath[FindAthlete(At_ID)];
	if (FindAthlete(At_ID) != -1)//�ҵ���
	{
		cout << "ID\t\t��Ŀ��" << endl;
		for (int i = 0; i < temp.GetCount(); i++)
		{
			cout << temp.GetProject(i) << endl;
		}
		cout << "��������Ҫ�Ǽǳɼ�����ĿID��";
		string Pr_ID;
		cin >> Pr_ID;
		string Pr_Name = pro[FindProject(Pr_ID)].GetName();
		cout << "�������˶�Ա " << temp.GetName() << " ����Ŀ " << Pr_Name << " �ĳɼ�Ϊ��";
		string Str_Score;
		cin >> Str_Score;
		ath[FindAthlete(At_ID)].SetStrScore(Pr_Name, Str_Score);//�ҵ��û���������Ŀ ����
		Save_apply_score();
		cout << "�Ǽǳɹ���" << endl;
		calculateScore(pro[FindProject(Pr_ID)].GetName());//�Զ��Ʒ�
		enter_end();
	}
	else
	{
		cout << "û�м�¼���˶�Ա������������ID��" << endl;
		enter_end();
		enrollScore();
		return;
	}
}
void AdminUI::generate_Match_list()//������������
{
	cout << "�������ɾ�������������" << endl;
	ofstream ofile;
	ofile.open("sports_score_system/��������.txt");
	ofile << "��������";
	for (int i = 0; i < p; i++)//��Ŀ
	{
		if (count_Athlete(pro[i].GetName()) == 0)//ͬ��Ŀ��������û�˾Ͳ����
			continue;
		calculateScore(pro[i].GetName());//�Ʒ�
		ofile << endl << "(" << pro[i].GetID() << ")" << pro[i].GetName() << "��";
		for (int j = 0; j < a; j++)//�ҳ����������Ŀƥ��ı���userID
		{
			if (ath[j].FindProject_ath(pro[i].GetName()) != -1 && ath[j].GetProject(ath[j].FindProject_ath(pro[i].GetName())).GetScore() != 0)//���˶�Ա������Ŀ���ҵ�
				ofile << endl << ath[j].GetID() << "\t" << ath[j].GetName();
		}
	}
	ofile.close();
	cout << "�ѱ�������ǰĿ¼�µ� ��������.txt ��" << endl;
	enter_end();
}
void AdminUI::calculateScore(string pro_name)//�Ʒ�
{
	int count = count_Athlete(pro_name);//ͳ��ĳ��Ŀ������ ��������
	Athlete temp[30];
	int a_count = 0;
	for (int i = 0; i < a; i++)
		if (ath[i].FindProject_ath(pro_name) != -1)//˵���˶�Ա�����˸���Ŀ
			temp[a_count++] = ath[i];
	//��temp�����ͬ��Ŀ���ճɼ�����
	for (int i = 0; i < a_count - 1; i++)
	{
		for (int j = 0; j < a_count - 1 - i; j++)
		{
			if (temp[j].GetStrScore(pro_name) > temp[j + 1].GetStrScore(pro_name))
			{
				Athlete temp2 = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = temp2;
			}
		}
	}
	int x = 0;//���ڴ�żƷֵĸ���
	//����
	if (count >= 16)//16������ ǰ���� 8��7��6��5��4��3��2��1
	{
		for (int i = 8; i > 0; i--)
			temp[8 - i].SetScore(pro_name, i);
		for (int i = 8;i < a_count; i++)
			temp[i].SetScore(pro_name, 0);
		x = 8;
	}
	else if (count >= 8)//8-16 ǰ���� 7��5��3��2��1
	{
		temp[0].SetScore(pro_name, 7);
		temp[1].SetScore(pro_name, 5);
		temp[2].SetScore(pro_name, 3);
		temp[3].SetScore(pro_name, 2);
		temp[4].SetScore(pro_name, 1);
		for (int i = 5; i < a_count; i++)
			temp[i].SetScore(pro_name, 0);
		x = 5;
	}
	else if (count < 8 && count > 0)//8������ ǰ���� 5��3��2
	{
		temp[0].SetScore(pro_name, 5);
		temp[1].SetScore(pro_name, 3);
		temp[2].SetScore(pro_name, 2);
		for (int i = 3; i < a_count; i++)
			temp[i].SetScore(pro_name, 0);
		x = 3;
	}
	//������õĳɼ�����temp�У�ת�Ƶ�athlete��
	for (int i = 0; i < x; i++)
		ath[FindAthlete(temp[i].GetID())].SetScore(pro_name, temp[i].GetScore(pro_name));
	Save_apply_score();//����
}
//ͳ��
void AdminUI::statistic_menu()
{
	cout << "###ͳ�Ʋ˵�###" << endl;
	cout << "(1)	ͳ�Ƹ�ѧԺ�ܷ�" << endl;
	cout << "(2)	��ѧԺ�ܷ�����" << endl;
	cout << "(3)	���������ܷ�����" << endl;
	cout << "(4)	��Ů�����ܷ�����" << endl;
	cout << "(5)	�鿴��Ŀǰ������" << endl;
	cout << "(6)	������һҳ" << endl;
	cout << "��ѡ��";
}
void AdminUI::statistic()
{
	int x;
	for (;;)
	{
		statistic_menu();
		cin >> x;
		system("cls");
		switch (x)
		{
		case 1:Statistic_total_college_score(); break;
		case 2:sort_college_score(); break;
		case 3:sort_score(1); break;//��
		case 4:sort_score(0); break;//Ů
		case 5:sort_project_list(); break;
		case 6:return;
		default:
		{
			cout << "��������������������룡" << endl;
			enter_end();
			statistic();
			return;
		}
		}
	}
}
void AdminUI::Statistic_total_college_score()//ͳ��ѧԺ�ܷ�
{
	cout << "����ͳ��ѧԺ�ܷ֡�����" << endl;
	ofstream ofile;
	ofile.open("sports_score_system/ѧԺ�ܷ�.txt");
	ofile << "ID\t\tѧԺ\t\t�ܷ�" << endl;
	for (int i = 0; i < c; i++)
		ofile << col[i] << "\t\t" << sum_score(col[i].GetName()) << endl;
	ofile.close();
	cout << "�ѱ�������ǰĿ¼�µ� ѧԺ�ܷ�.txt ��" << endl;
	enter_end();
}
void AdminUI::sort_college_score()//��ѧԺ�ܷ�����
{
	struct col_Score
	{
		string ID;
		string Name;
		float Score;
	};
	col_Score temp[100];
	int count = 0;
	for (int i = 0; i < c; i++)
	{
		temp[count].ID = col[i].GetID();
		temp[count].Name = col[i].GetName();
		temp[count].Score = sum_score(col[i].GetName());
		count++;
	}
	//����
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (temp[j].Score < temp[j + 1].Score)//�Ӵ�С
			{
				col_Score temp2 = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = temp2;
			}
		}
	}
	cout << "ID\t\tѧԺ\t\t�ܷ�" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << temp[i].ID << "\t\t" << temp[i].Name << "\t\t" << temp[i].Score << endl;
	}
	enter_end();
}
void AdminUI::sort_score(bool sex)//����Ů�������ܷ�����//0 Ů 1��
{
	for (int i = 0; i < p; i++)
	{
		cout << "(" << pro[i].GetID() << ")" << pro[i].GetName() << endl;
		struct col_Score
		{
			string ID;
			string Name;
			float Score;
		};
		col_Score temp[30];
		int count = 0;
		for (int j = 0; j < c; j++)//�����ͬѧԺ��Ⱥ���ܷ�
		{
			float count_score = 0;
			for (int k = 0; k < a; k++)//�����˶�Ա
			{
				if (ath[k].GetSex() == sex && ath[k].FindProject_ath(pro[i].GetName()) != -1 && col[j].GetName()==ath[k].GetCollege())
					//��Ӧ�Ա� רҵ��ͬ ���ҵ���Ŀ
				{
					count_score += ath[k].GetScore(pro[i].GetName());
				}
			}
			temp[count].ID = col[j].GetID();
			temp[count].Name = col[j].GetName();
			temp[count].Score = count_score;
			count++;
		}
		//����
		for (int j = 0; j < count - 1; j++)
		{
			for (int k = 0; k < count - 1 - i; k++)
			{
				if (temp[k].Score < temp[k + 1].Score)//�Ӵ�С
				{
					col_Score temp2 = temp[k];
					temp[k] = temp[k + 1];
					temp[k + 1] = temp2;
				}
			}
		}
		cout << "ID\t\tѧԺ\t\t�ܷ�" << endl;
		for (int j = 0; j < count; j++)
		{
			cout << temp[j].ID << "\t\t" << temp[j].Name << "\t\t" << temp[j].Score << endl;
		}
	}
	enter_end();
}
void AdminUI::sort_project_list()//�鿴��Ŀǰ����������
{
	ShowProject();
	string pro_ID;
	cout << "��������Ҫ��ѯ����ĿID��";
	cin >> pro_ID;
	system("cls");
	string pro_name = pro[FindProject(pro_ID)].GetName();
	int count = count_Athlete(pro_name);//ͬһ��Ŀ������
	//����
	Athlete temp[30];
	int a_count = 0;
	for (int i = 0; i < a; i++)
		if (ath[i].FindProject_ath(pro_name) != -1)//˵���˶�Ա�����˸���Ŀ
			temp[a_count++] = ath[i];
	//��temp�����ͬ��Ŀ���ճɼ�����
	for (int i = 0; i < a_count - 1; i++)
	{
		for (int j = 0; j < a_count - 1 - i; j++)
		{
			if (temp[j].GetScore(pro_name) < temp[j + 1].GetScore(pro_name))
			{
				Athlete temp2 = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = temp2;
			}
		}
	}
	int x = 0;//���ڴ�żƷֵĸ���
	if (count >= 16)//16������ ǰ����
		x = 8;
	else if (count >= 8)//8-16 ǰ����
		x = 5;
	else if (count < 8 && count > 0)//8������ ǰ����
		x = 3;
	cout << pro_name << "ǰ" << x << "���ĵ÷�Ϊ��" << endl;
	cout << "ID\t\t����\t\t�÷�" << endl;
	for (int j = 0; j < x; j++)
	{
		cout << temp[j].GetID() << "\t" << ath[FindAthlete(temp[j].GetID())].GetName() << "\t\t" << temp[j].GetScore(pro_name) << endl;
	}
	enter_end();
}