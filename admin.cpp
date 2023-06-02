#include "admin.h"
#include <conio.h>//_getch()
#include "io.h"//_access()
#include <fstream>//文件操作
#include <iostream>//输入输出
#include <algorithm>//sort
#include <stdlib.h>//system()
using namespace std;
int Admin::A = 8;//同系不超过8人
int Admin::B = 30;//整个人数不超过30人
Admin::Admin()
{
    c = 0;
    p = 0;
    a = 0;
    ReadCollege();
    ReadProject();
    ReadAthlete();
    ReadApply();
}
Admin::~Admin()
{
    if (c != 0)
        SaveCollege();
    if (p != 0)
        SaveProject();
    if (a != 0)
        SaveAthlete();
    if (_access("sports_score_system/apply_score.txt", 0) != -1)//文件存在
    {
        Save_apply_score();
    }
}
void Admin::enter_end()//按下回车键才结束
{
    cout << endl;
    cout << "*按下回车键返回*";
    int ch;
    while (ch = _getch())
    {
        if (ch == '\r')
        {
            system("cls");
            return;
        }
    }
}
//展示信息
void Admin::ShowCollege() 
{
    if (c == 0)//无学院
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    Sort_by_ID(col);//按ID排序再输出
    cout << "ID\t\t学院名" << endl;
    for (int i = 0; i < c; i++)
        cout << col[i] << endl;
}
void Admin::ShowProject()
{
    if (p == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    Sort_by_ID(pro);
    cout << "ID\t\t项目名\t\t时间" << endl;
    for (int i = 0; i < p; i++)
        cout << pro[i] << "\t\t" << pro[i].GetTime() << endl;
}
void Admin::ShowAthlete()
{
    if (a == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    Sort_by_ID(ath);
    cout << "ID\t\t姓名\t性别\t学院" << endl;
    for (int i = 0; i < a; i++)
        cout << ath[i] <<"\t"<< ath[i].GetCollege() << endl;
}
//信息添加
void Admin::AddCollege()
{
    string name;
    cout << "请输入学院名：";
    cin >> name;//名称不得重复
    if (FindCollege(name) == -1)//没找到
    {
        //ID得考虑前面ID被删除的情况
        for (int ID = 1; ID <= c + 1; ID++)//c+1保证编号正好是c，因为此时c未+1
        {
            if (FindCollege(to_string(ID)) == -1)//没找到那个ID
            {
                col[c].SetID(to_string(ID));
                break;
            }
        }
        col[c].SetName(name);
        c++;
        SaveCollege();//保存一次数据
        cout << "添加成功！" << endl;
        enter_end();//按回车结束
    }
    else
    {
        cout << "名称不得重复！请重新尝试！" << endl;
        enter_end();
        AddCollege();
        return;
    }
}
void Admin::AddProject()
{
    string name;
    cout << "请输入项目名：";
    cin >> name;
    if (FindProject(name) == -1)//没找到
    {
        //ID得考虑前面ID被删除的情况
        for (int ID = 1; ID <= p + 1; ID++)//此时p并未+1
        {
            if (FindProject(to_string(ID)) == -1)//没找到那个ID
            {
                pro[p].SetID(to_string(ID));
                break;
            }
        }
        pro[p].SetName(name);
        cout << "请输入项目的比赛时间(年月日 时分)：";
        Date times;
        cin >> times;
        pro[p].SetTime(times);
        p++;
        SaveProject();//保存项目
        cout << "添加成功！" << endl;
        enter_end();//回车结束
    }
    else
    {
        cout << "名称不得重复！请重新尝试！" << endl;
        enter_end();
        AddProject();
        return;
    }
}
void Admin::AddAthlete()
{
    cout << "请输入运动员ID、姓名、性别(男/女)、学院(用空格或Tap间隔)" << endl;
    string ID, at_name, sex, col_name;
    cin >> ID >> at_name >> sex >> col_name;
    if (FindAthlete(ID) == -1)//没找到
    {
        //检查添加的用户的学院是否存在
        if (FindCollege(col_name) == -1)//没找到该学院名
        {
            cout << "您输入的学院不存在！请重新输入！" << endl;
            enter_end();
            AddAthlete();
            return;
        }
        //存在该学院
        ath[a].SetID(ID);
        ath[a].SetName(at_name);
        ath[a].SetSex((sex == "男" ? 1 : 0));
        ath[a].SetCollege(col_name);
        a++;
        SaveAthlete();//保存运动员数据
        cout << "添加成功！" << endl;
        enter_end();
    }
    else
    {
        cout << "ID不得重复！请重新尝试！" << endl;
        enter_end();
        AddAthlete();
        return;
    }
}
//信息删除
void Admin::RemoveCollege()
{
    if (c == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    ShowCollege();
    cout << "###学院信息的删除###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  学院名" << endl;
    cout << "请选择您要查找的选项：";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "请输入您要删除的学院ID："; break;
    case 2:cout << "请输入要删除的学院名称："; break;
    default:
    {
        cout << "您输入的有误！请重新输入！" << endl;
        enter_end();
        RemoveCollege();
        return;
    }
    }
    cin >> temp;
    if (FindCollege(temp) != -1)//找到了
    {
        cout << "已确认您要删除的学院为：";
        cout << col[FindCollege(temp)].GetName() << endl;
        for (int i = FindCollege(temp); i < c - 1; i++)
            col[i] = col[i + 1];
        c--;
        SaveCollege();
        cout << "删除成功！" << endl;
    }
    else//没找到
        cout << "没有找到！" << endl;
    enter_end();
}
void Admin::RemoveProject()
{
    if (p == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    ShowProject();
    cout << "###项目信息的删除###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  项目名" << endl;
    cout << "请选择您要查找的选项：";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "请输入您要删除的项目ID："; break;
    case 2:cout << "请输入要删除的项目名称："; break;
    default:
    {
        cout << "您输入的有误！请重新输入！" << endl;
        enter_end();
        RemoveProject();
        return;
    }
    }
    cin >> temp;
    if (FindProject(temp) != -1)//找到了该项目的ID
    {
        cout << "已确认您要删除的项目为：";
        cout << pro[FindProject(temp)].GetName() << endl;
        for (int i = FindProject(temp); i < p - 1; i++)
            pro[i] = pro[i + 1];
        p--;
        SaveProject();
        cout << "删除成功！" << endl;
    }
    else
        cout << "没有找到！" << endl;
    enter_end();
}
void Admin::RemoveAthlete()
{
    if (a == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    ShowAthlete();
    cout << "###运动员信息的删除###" << endl;
    string ID;
    cout << "请输入您要删除运动员的ID：";
    cin >> ID;
    if (FindAthlete(ID) != -1)//找到了该运动员的ID
    {
        cout << "已确认您要删除的运动员为：";
        cout << "ID：" << ath[FindAthlete(ID)].GetID() << "\t姓名：" << ath[FindAthlete(ID)].GetName() << endl;
        for (int i = FindAthlete(ID); i < a - 1; i++)
            ath[i] = ath[i + 1];
        a--;
        SaveAthlete();
        cout << "删除成功！" << endl;
    }
    else
        cout << "没有找到该ID！" << endl;
    enter_end();
}
//信息修改
void Admin::SetCollege()
{
    if (c == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    ShowCollege();
    cout << "###学院信息的修改###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  学院名" << endl;
    cout << "请选择您要查找的选项：";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "请输入目标ID："; break;
    case 2:cout << "请输入目标名称："; break;
    default:
    {
        cout << "您输入的有误！请重新输入！" << endl;
        enter_end();
        SetCollege();
        return;
    }
    }
    cin >> temp;
    if (FindCollege(temp) != -1)//找到
    {
        cout << "查找到的学院信息为：" << endl;
        cout << "ID\t\t学院名" << endl;
        cout << col[FindCollege(temp)] << endl;
        string name;
        cout << "请输入您要修改的名称：";
        cin >> name;
        //检查名称是否已经存在
        if (FindCollege(name) != -1)//找到
        {
            cout << "该名称重复！" << endl;
            enter_end();
            return;
        }
        col[FindCollege(temp)].SetName(name);
        SaveCollege();
        cout << "修改成功！" << endl;
        cout << "ID\t学院名" << endl;
        cout << col[FindCollege(temp)] << endl;
    }
    else
        cout << "没有找到！" << endl;
    enter_end();
}
void Admin::SetProject()
{
    if (p == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    ShowProject();
    cout << "###项目信息的修改###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  项目名" << endl;
    cout << "请选择您要查找的选项：";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "请输入目标ID："; break;
    case 2:cout << "请输入目标名称："; break;
    default:
    {
        cout << "您输入的有误！请重新输入！" << endl;
        enter_end();
        SetProject();
        return;
    }
    }
    cin >> temp;
    if (FindProject(temp) != -1)//找到
    {
        cout << "查找到的项目信息为：" << endl;
        cout << "ID\t\t项目名\t时间" << endl;
        cout << pro[FindProject(temp)] << pro[FindProject(temp)].GetTime() << endl;
        cout << "(1)项目名   (2)时间" << endl;
        cout << "请输入您要修改的选项：";
        int j;
        cin >> j;
        switch (j)
        {
        case 1:
        {
            string name;
            cout << "请输入您要修改的名称：";
            cin >> name;
            //检查名称是否已经存在
            if (FindProject(name) != -1)//找到
            {
                cout << "该名称重复！" << endl;
                enter_end();
                return;
            }
            pro[FindProject(temp)].SetName(name);
            break;
        }
        case 2:
        {
            Date time;
            cout << "请输入您要修改的时间：";
            cin >> time;
            pro[FindProject(temp)].SetTime(time);
            break;
        }
        default:
        {
            cout << "您输入的有误！请重新输入！" << endl;
            enter_end();
            return;
        }
        }
        SaveProject();
        cout << "修改成功！" << endl;
        cout << "ID\t\t项目名\t时间" << endl;
        cout << pro[FindProject(temp)] << pro[FindProject(temp)].GetTime() << endl;
    }
    else
        cout << "没有找到！" << endl;
    enter_end();
}
void Admin::SetAthlete()
{
    if (a == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    ShowAthlete();
    cout << "###运动员信息的修改###" << endl;
    string ID;
    cout << "请输入您要修改运动员的ID：";
    cin >> ID;
    if (FindAthlete(ID) != -1)//找到了该运动员的ID
    {
        int temp = FindAthlete(ID);
        cout << "查找到的运动员信息为：" << endl;
        cout << "ID\t\t姓名\t性别\t学院" << endl;
        cout << ath[temp] << ath[temp].GetCollege() << endl;
        cout << "(1)姓名\t(2)性别\t(3)学院" << endl;
        cout << "请输入您要修改的选项：";
        int i;
        cin >> i;
        switch (i)
        {
        case 1://姓名
        {
            cout << "请输入您要修改的姓名：";
            string name;
            cin >> name;
            ath[temp].SetName(name);
            break;
        }
        case 2://性别
        {
            cout << "请输入您要修改的性别(男/女)：";
            string sex;
            cin >> sex;
            ath[temp].SetSex(sex == "男" ? 1 : 0);
            break;
        }
        case 3://学院
        {
            cout << "请输入您要修改的学院：";
            string col_name;
            cin >> col_name;
            ath[temp].SetCollege(col_name);
            break;
        }
        default:
        {
            cout << "您输入的有误！请重新输入！" << endl;
            enter_end();
            SetAthlete();
            return;
        }
        }
        SaveAthlete();
        cout << "修改成功！" << endl;
        cout << "ID\t\t姓名\t性别\t学院" << endl;
        cout << ath[temp] << ath[temp].GetCollege() << endl;
    }
    else
        cout << "没有找到该ID！" << endl;
    enter_end();
}
//信息查询
int Admin::FindCollege(string str)
{
    for (int i = 0; i < c; i++)
        if (col[i].GetID() == str || col[i].GetName() == str)
            return i;
    return -1;
}
int Admin::FindProject(string str)
{
    for (int i = 0; i < p; i++)
        if (pro[i].GetID() == str || pro[i].GetName() == str)
            return i;
    return -1;
}
int Admin::FindAthlete(string str)
{
    for (int i = 0; i < a; i++)
        if (ath[i].GetID() == str || ath[i].GetName() == str)
            return i;
    return -1;
}
void Admin::FindCollege()
{
    if (c == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    cout << "###学院信息的查找###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  学院名" << endl;
    cout << "请选择您要查找的选项：";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1: cout << "请输入学院ID："; break;
    case 2:cout << "请输入学院名："; break;
    default:
    {
        cout << "您输入的有误！请重新输入！" << endl;
        enter_end();
        FindCollege();
        return;
    }
    }
    cin >> temp;
    if (FindCollege(temp) != -1)
    {
        cout << "找到了对应 " << temp << " 的数据！" << endl;
        cout << "ID\t学院名" << endl;
        cout << col[FindCollege(temp)] << endl;
    }
    else
        cout << "没有找到对应 " << temp << " 的数据！" << endl;
    enter_end();
}
void Admin::FindProject()
{
    if (p == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    cout << "###项目信息的查找###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  项目名" << endl;
    cout << "请选择您要查找的选项：";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "请输入项目ID："; break;
    case 2:cout << "请输入学院名："; break;
    default:
    {
        cout << "您输入的有误！请重新输入！" << endl;
        enter_end();
        FindProject();
        return;
    }
    }
    cin >> temp;
    if (FindProject(temp) != -1)
    {
        cout << "找到了对应 " << temp << " 的数据！" << endl;
        cout << "ID\t项目名" << endl;
        cout << pro[FindProject(temp)] << endl;
    }
    else
        cout << "没有找到对应 " << temp << " 的数据！" << endl;
    enter_end();
}
void Admin::FindAthlete()
{
    if (a == 0)
    {
        cout << "没有任何数据！" << endl;
        enter_end();
        return;
    }
    cout << "###运动员信息的查找###" << endl;
    cout << "请输入运动员ID：";
    string ID;
    cin >> ID;
    if (FindAthlete(ID) != -1)
    {
        cout << "找到了对应 " << ID << " 的数据！" << endl;
        cout << "ID\t\t姓名\t性别\t学院" << endl;
        cout << ath[FindAthlete(ID)] << ath[FindAthlete(ID)].GetCollege() << endl;
    }
    else
        cout << "没有找到对应 " << ID << " 的数据！" << endl;
    enter_end();
}
//信息保存//全部信息保存
void Admin::SaveCollege()
{
    ofstream ofile;
    ofile.open("sports_score_system/colleges.txt");
    ofile << "ID\t\t学院名";
    Sort_by_ID(col);
    for (int i = 0; i < c; i++)
    {
        ofile << endl << col[i];
    }
    ofile.close();
}
void Admin::SaveProject()
{
    ofstream ofile;
    ofile.open("sports_score_system/projects.txt");
    ofile << "ID\t\t项目名\t\t比赛时间";
    Sort_by_ID(pro);
    for (int i = 0; i < p; i++)
    {
        ofile << endl << pro[i] << "\t\t\t" << pro[i].GetTime();
    }
    ofile.close();
}
void Admin::SaveAthlete()
{
    ofstream ofile;
    ofile.open("sports_score_system/athletes.txt");
    ofile << "ID\t\t\t姓名\t\t性别\t\t学院";
    Sort_by_ID(ath);
    for (int i = 0; i < a; i++)
    {
        ofile << endl << ath[i].GetID() << "\t" << ath[i].GetName() << "\t" << (ath[i].GetSex() == 0 ? "女" : "男") << "\t\t" << ath[i].GetCollege();
    }
    ofile.close();
}
void Admin::Save_apply_score()//保存报名与分数信息(报名时，分数默认为0)
{
    ofstream ofile;
    ofile.open("sports_score_system/apply_score.txt");
    ofile << "UserID\t\t\tProjectID\t\tScore\tStr_Score";//标题
    for (int i = 0; i < a; i++)//所有运动员
    {
        if (ath[i].GetCount() > 0)//说明该运动员有报名记录
        {
            for (int j = 0; j < ath[i].GetCount(); j++)
            {
                ofile << endl << ath[i].GetID() << "\t\t" << ath[i].GetProject(j).GetID() << "\t\t\t" << ath[i].GetProject(j).GetScore() << "\t\t" << ath[i].GetProject(j).GetStrScore();
            }
        }
    }
    ofile.close();
}
//信息读取
void Admin::ReadCollege()
{
    if (_access("sports_score_system/colleges.txt", 0) != -1)//文件存在
    {
        ifstream ifile;
        ifile.open("sports_score_system/colleges.txt");
        string line;
        getline(ifile, line);
        while (!ifile.eof())
        {
            ifile >> col[c++];
        }
        ifile.close();
    }
}
void Admin::ReadProject()
{
    if (_access("sports_score_system/projects.txt", 0) != -1)//文件存在
    {
        ifstream ifile;
        ifile.open("sports_score_system/projects.txt");
        string line;
        getline(ifile, line);//存放标题
        Date times;//存放时间
        while (!ifile.eof())
        {
            ifile >> pro[p] >> times;
            pro[p].SetTime(times);//设置时间
            p++;
        }
        ifile.close();
    }
}
void Admin::ReadAthlete()
{
    if (_access("sports_score_system/athletes.txt", 0) != -1)//文件存在
    {
        ifstream ifile;
        ifile.open("sports_score_system/athletes.txt");
        string line;
        getline(ifile, line);//存放标题
        string col_name;
        while (!ifile.eof())
        {
            ifile >> ath[a] >> col_name;
            ath[a].SetCollege(col_name);
            a++;
        }
        ifile.close();
    }
}
void Admin::ReadApply()//读取报名信息
{
    if (_access("sports_score_system/apply_score.txt", 0) != -1)//文件存在
    {
        ifstream ifile;
        ifile.open("sports_score_system/apply_score.txt");
        string line;//存放标题
        getline(ifile, line);
        while (!ifile.eof())
        {
            string UserID, ProID, StrScore;
            float Score;
            ifile >> UserID >> ProID >> Score >> StrScore;
            ath[FindAthlete(UserID)].AddProject(ProID,pro[FindProject(ProID)].GetName());
            ath[FindAthlete(UserID)].SetScore(pro[FindProject(ProID)].GetName(), Score);
            ath[FindAthlete(UserID)].SetStrScore(pro[FindProject(ProID)].GetName(), StrScore);
        }
        ifile.close();
    }
}
//排序
bool compare_ID_col(College& a, College& b)
{
    return a.GetID() < b.GetID();
}
bool compare_ID_pro(Project& a, Project& b)
{
    return a.GetID() < b.GetID();
}
bool compare_ID_ath(Athlete& a, Athlete& b)
{
    return a.GetID() < b.GetID();
}
void Admin::Sort_by_ID(College[])
{
    sort(col, col + c, compare_ID_col);
}
void Admin::Sort_by_ID(Project[])
{
    sort(pro, pro + p, compare_ID_pro);
}
void Admin::Sort_by_ID(Athlete[])
{
    sort(ath, ath + a, compare_ID_ath);
}
//人数
int Admin::count_Athlete_sex(string pro_name, bool sex)//整个项目男女报名人数//0 女 /1 男
{
    //遍历运动员，找出报名该项目的人，判断性别
    int women_count = 0, man_count = 0;//女生人数，男生人数
    for (int i = 0; i < a; i++)//遍历运动员
    {
        if (ath[i].GetCount() > 0 && ath[i].FindProject_ath(pro_name) != -1)
        {
            if (ath[i].GetSex() == 1)
                man_count++;
            else
                women_count++;
        }
    }
    if (sex == 0)
        return women_count;
    else
        return man_count;
}
int Admin::count_Athlete_college(string pro_name, string col_name)//同系报名人数//项目/专业
{
    int count = 0;
    for (int i = 0; i < a; i++)
        if (ath[i].GetCollege()==col_name && ath[i].FindProject_ath(pro_name)!=-1)
            count++;
    return count;
}
int Admin::count_Athlete(string pro_name)//整个学院某一项目报名人数
{
    int count = 0;
    for (int i = 0; i < a; i++)
    {
        if (ath[i].FindProject_ath(pro_name) != -1)//有报名项目
            count++;
    }
    return count;
}
float Admin::sum_score(string col_name)//学院名//计算某学院的总分
{
    float sum_score = 0;
    for (int i = 0; i < a; i++)
    {
        for(int j=0;j<ath[i].GetCount();j++)
        {
            float score = ath[i].GetProject(j).GetScore();
            if (ath[i].GetCollege() == col_name &&  score != 0)//匹配的上学院名
            {
                sum_score += score;
            }
        }
    }
    return sum_score;
}