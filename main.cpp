#include "adminUI.h"
#include "athleteUI.h"
#include "usersUI.h"
using namespace std;
void main()
{
	bool f = false;
	for (;;)
	{
		UsersUI use;
		use.menu();
		int n = use.GetGM();
		if (n == -1)//û�е�¼
			return;
		f = false;
		system("cls");
		if (n == 1)
		{
			AdminUI ad;
			int x;
			for (;;)
			{
				ad.menu();
				cin >> x;
				system("cls");
				switch (x)
				{
				case 1:ad.information(); break;
				case 2:ad.generate_name_list(); break;
				case 3:ad.enrollScore(); break;
				case 4:ad.generate_Match_list(); break;
				case 5:ad.statistic(); break;
				case 6:
				{
					f = true;
					break;
				}
				case 7:cout << "��ӭʹ�ñ�ϵͳ���ټ���" << endl; return;
				default:cout << "û�и�ѡ�������ѡ��" << endl; break;
				}
				if (f == true)	break;
			}
		}
		else
		{
			AthleteUI at;
			at.SetUserID(use.GetID());
			int x;
			for (;;)
			{
				at.menu();
				cin >> x;
				system("cls");
				switch (x)
				{
				case 1:at.DisplayProjects(); break;
				case 2:at.Applicate(); break;
				case 3:at.Find_myself(); break;
				case 4:at.Display_total_college_score(); break;
				case 5://�˳���¼
				{
					f = true;
					break;
				}
				case 6:cout << "��ӭʹ�ñ�ϵͳ���ټ���" << endl; return;
				default:cout << "û�и�ѡ�������ѡ��" << endl; break;
				}
				if (f == true)	break;
			}
		}
	}
}