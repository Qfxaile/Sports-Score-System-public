#include "adminUI.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
void AdminUI::menu()
{
	cout << "###欢迎来到管理员页面###" << endl;
	cout << "(1)	信息处理" << endl;
	cout << "(2)	生成报名表" << endl;
	cout << "(3)	登记成绩" << endl;
	cout << "(4)	生成决赛名单" << endl;
	cout << "(5)	统计" << endl;
	cout << "(6)	退出登录" << endl;
	cout << "(7)	退出系统" << endl;
	cout << "请选择：";
}
void AdminUI::infor_menu()
{
	cout << "###信息处理###" << endl;
	cout << "(1)	学院信息" << endl;
	cout << "(2)	项目信息" << endl;
	cout << "(3)	运动员信息" << endl;
	cout << "(4)	返回上一页" << endl;
	cout << "请选择：";
}
void AdminUI::infor2_menu()
{
	cout << "(1)	添加" << endl;
	cout << "(2)	修改" << endl;
	cout << "(3)	查询" << endl;
	cout << "(4)	删除" << endl;
	cout << "(5)	展示信息" << endl;
	cout << "(6)	返回上一页" << endl;
	cout << "(7)	返回主界面" << endl;
	cout << "请选择：";
}
void AdminUI::information()//信息处理
{
	int i;
	for (;;)
	{
		infor_menu();
		cin >> i;
		system("cls");
		switch (i)
		{
		case 1://学院信息
		{
			int n;
			for (;;)
			{
				cout << "###学院信息###" << endl;
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
		case 2://项目信息
		{
			int n;
			for (;;)
			{
				cout << "###项目信息###" << endl;
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
		case 3://运动员信息
		{
			int n;
			for (;;)
			{
				cout << "###运动员信息###" << endl;
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
		case 4:system("cls");return;//返回上一页
		default:
		{
			cout << "您输入的有误！请重新输入！" << endl;
			enter_end();
			information();
			return;
		}
		}
	}
}
void AdminUI::generate_name_list()//生成报名表
{
	cout << "正在生成报名表。。。" << endl;
	ofstream ofile;
	ofile.open("sports_score_system/报名表.txt");
	ofile << "报名信息";
	for (int i = 0; i < p; i++)//项目
	{
		if (count_Athlete(pro[i].GetName()) == 0)//获取同项目报名人数
			continue;
		ofile << endl << "(" << pro[i].GetID() << ")" << pro[i].GetName() << "：";
		for (int j = 0; j < a; j++)//找出所有与该项目匹配的报名userID
		{
			if (ath[j].FindProject_ath(pro[i].GetName())!=-1)//在运动员报名项目中找到
			{
				ofile << endl << ath[j].GetID() << "\t" << ath[j].GetName();
			}
		}
	}
	ofile.close();
	cout << "已保存至当前目录下的 报名表.txt 中" << endl;
	enter_end();
}
void AdminUI::maintain_menu()
{
	cout << "###维护报名表###" << endl;
	cout << "(1)	添加" << endl;
	cout << "(2)	删除" << endl;
	cout << "(3)	修改" << endl;
	cout << "(4)	排序" << endl;
	cout << "(5)	返回上一页" << endl;
	cout << "请选择：";
}
void AdminUI::enrollScore()//登记成绩
{
	ShowAthlete();
	cout << "请输入您要登记成绩的运动员的ID：";
	string At_ID;
	cin >> At_ID;
	Athlete temp = ath[FindAthlete(At_ID)];
	if (FindAthlete(At_ID) != -1)//找到了
	{
		cout << "ID\t\t项目名" << endl;
		for (int i = 0; i < temp.GetCount(); i++)
		{
			cout << temp.GetProject(i) << endl;
		}
		cout << "请输入您要登记成绩的项目ID：";
		string Pr_ID;
		cin >> Pr_ID;
		string Pr_Name = pro[FindProject(Pr_ID)].GetName();
		cout << "请输入运动员 " << temp.GetName() << " 在项目 " << Pr_Name << " 的成绩为：";
		string Str_Score;
		cin >> Str_Score;
		ath[FindAthlete(At_ID)].SetStrScore(Pr_Name, Str_Score);//找到用户报名的项目 赋分
		Save_apply_score();
		cout << "登记成功！" << endl;
		calculateScore(pro[FindProject(Pr_ID)].GetName());//自动计分
		enter_end();
	}
	else
	{
		cout << "没有记录该运动员！请重新输入ID！" << endl;
		enter_end();
		enrollScore();
		return;
	}
}
void AdminUI::generate_Match_list()//产生比赛名单
{
	cout << "正在生成决赛名单。。。" << endl;
	ofstream ofile;
	ofile.open("sports_score_system/决赛名单.txt");
	ofile << "决赛名单";
	for (int i = 0; i < p; i++)//项目
	{
		if (count_Athlete(pro[i].GetName()) == 0)//同项目报名人数没人就不输出
			continue;
		calculateScore(pro[i].GetName());//计分
		ofile << endl << "(" << pro[i].GetID() << ")" << pro[i].GetName() << "：";
		for (int j = 0; j < a; j++)//找出所有与该项目匹配的报名userID
		{
			if (ath[j].FindProject_ath(pro[i].GetName()) != -1 && ath[j].GetProject(ath[j].FindProject_ath(pro[i].GetName())).GetScore() != 0)//在运动员报名项目中找到
				ofile << endl << ath[j].GetID() << "\t" << ath[j].GetName();
		}
	}
	ofile.close();
	cout << "已保存至当前目录下的 决赛名单.txt 中" << endl;
	enter_end();
}
void AdminUI::calculateScore(string pro_name)//计分
{
	int count = count_Athlete(pro_name);//统计某项目总人数 进行排名
	Athlete temp[30];
	int a_count = 0;
	for (int i = 0; i < a; i++)
		if (ath[i].FindProject_ath(pro_name) != -1)//说明运动员报名了该项目
			temp[a_count++] = ath[i];
	//将temp里面的同项目按照成绩排序
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
	int x = 0;//用于存放计分的个数
	//积分
	if (count >= 16)//16人以上 前八名 8、7、6、5、4、3、2、1
	{
		for (int i = 8; i > 0; i--)
			temp[8 - i].SetScore(pro_name, i);
		for (int i = 8;i < a_count; i++)
			temp[i].SetScore(pro_name, 0);
		x = 8;
	}
	else if (count >= 8)//8-16 前五名 7、5、3、2、1
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
	else if (count < 8 && count > 0)//8人以下 前三名 5、3、2
	{
		temp[0].SetScore(pro_name, 5);
		temp[1].SetScore(pro_name, 3);
		temp[2].SetScore(pro_name, 2);
		for (int i = 3; i < a_count; i++)
			temp[i].SetScore(pro_name, 0);
		x = 3;
	}
	//将计算好的成绩（在temp中）转移到athlete中
	for (int i = 0; i < x; i++)
		ath[FindAthlete(temp[i].GetID())].SetScore(pro_name, temp[i].GetScore(pro_name));
	Save_apply_score();//保存
}
//统计
void AdminUI::statistic_menu()
{
	cout << "###统计菜单###" << endl;
	cout << "(1)	统计各学院总分" << endl;
	cout << "(2)	按学院总分排序" << endl;
	cout << "(3)	按男团体总分排序" << endl;
	cout << "(4)	按女团体总分排序" << endl;
	cout << "(5)	查看项目前几名单" << endl;
	cout << "(6)	返回上一页" << endl;
	cout << "请选择：";
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
		case 3:sort_score(1); break;//男
		case 4:sort_score(0); break;//女
		case 5:sort_project_list(); break;
		case 6:return;
		default:
		{
			cout << "您输入的有误！请重新输入！" << endl;
			enter_end();
			statistic();
			return;
		}
		}
	}
}
void AdminUI::Statistic_total_college_score()//统计学院总分
{
	cout << "正在统计学院总分。。。" << endl;
	ofstream ofile;
	ofile.open("sports_score_system/学院总分.txt");
	ofile << "ID\t\t学院\t\t总分" << endl;
	for (int i = 0; i < c; i++)
		ofile << col[i] << "\t\t" << sum_score(col[i].GetName()) << endl;
	ofile.close();
	cout << "已保存至当前目录下的 学院总分.txt 中" << endl;
	enter_end();
}
void AdminUI::sort_college_score()//按学院总分排序
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
	//排序
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (temp[j].Score < temp[j + 1].Score)//从大到小
			{
				col_Score temp2 = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = temp2;
			}
		}
	}
	cout << "ID\t\t学院\t\t总分" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << temp[i].ID << "\t\t" << temp[i].Name << "\t\t" << temp[i].Score << endl;
	}
	enter_end();
}
void AdminUI::sort_score(bool sex)//按男女生团体总分排序//0 女 1男
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
		for (int j = 0; j < c; j++)//算出不同学院的群体总分
		{
			float count_score = 0;
			for (int k = 0; k < a; k++)//遍历运动员
			{
				if (ath[k].GetSex() == sex && ath[k].FindProject_ath(pro[i].GetName()) != -1 && col[j].GetName()==ath[k].GetCollege())
					//对应性别 专业相同 能找到项目
				{
					count_score += ath[k].GetScore(pro[i].GetName());
				}
			}
			temp[count].ID = col[j].GetID();
			temp[count].Name = col[j].GetName();
			temp[count].Score = count_score;
			count++;
		}
		//排序
		for (int j = 0; j < count - 1; j++)
		{
			for (int k = 0; k < count - 1 - i; k++)
			{
				if (temp[k].Score < temp[k + 1].Score)//从大到小
				{
					col_Score temp2 = temp[k];
					temp[k] = temp[k + 1];
					temp[k + 1] = temp2;
				}
			}
		}
		cout << "ID\t\t学院\t\t总分" << endl;
		for (int j = 0; j < count; j++)
		{
			cout << temp[j].ID << "\t\t" << temp[j].Name << "\t\t" << temp[j].Score << endl;
		}
	}
	enter_end();
}
void AdminUI::sort_project_list()//查看项目前几名的名单
{
	ShowProject();
	string pro_ID;
	cout << "请输入您要查询的项目ID：";
	cin >> pro_ID;
	system("cls");
	string pro_name = pro[FindProject(pro_ID)].GetName();
	int count = count_Athlete(pro_name);//同一项目的人数
	//排序
	Athlete temp[30];
	int a_count = 0;
	for (int i = 0; i < a; i++)
		if (ath[i].FindProject_ath(pro_name) != -1)//说明运动员报名了该项目
			temp[a_count++] = ath[i];
	//将temp里面的同项目按照成绩排序
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
	int x = 0;//用于存放计分的个数
	if (count >= 16)//16人以上 前八名
		x = 8;
	else if (count >= 8)//8-16 前五名
		x = 5;
	else if (count < 8 && count > 0)//8人以下 前三名
		x = 3;
	cout << pro_name << "前" << x << "名的得分为：" << endl;
	cout << "ID\t\t姓名\t\t得分" << endl;
	for (int j = 0; j < x; j++)
	{
		cout << temp[j].GetID() << "\t" << ath[FindAthlete(temp[j].GetID())].GetName() << "\t\t" << temp[j].GetScore(pro_name) << endl;
	}
	enter_end();
}