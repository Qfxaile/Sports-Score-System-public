#include "admin.h"
#include <conio.h>//_getch()
#include "io.h"//_access()
#include <fstream>//�ļ�����
#include <iostream>//�������
#include <algorithm>//sort
#include <stdlib.h>//system()
using namespace std;
int Admin::A = 8;//ͬϵ������8��
int Admin::B = 30;//��������������30��
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
    if (_access("sports_score_system/apply_score.txt", 0) != -1)//�ļ�����
    {
        Save_apply_score();
    }
}
void Admin::enter_end()//���»س����Ž���
{
    cout << endl;
    cout << "*���»س�������*";
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
//չʾ��Ϣ
void Admin::ShowCollege() 
{
    if (c == 0)//��ѧԺ
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    Sort_by_ID(col);//��ID���������
    cout << "ID\t\tѧԺ��" << endl;
    for (int i = 0; i < c; i++)
        cout << col[i] << endl;
}
void Admin::ShowProject()
{
    if (p == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    Sort_by_ID(pro);
    cout << "ID\t\t��Ŀ��\t\tʱ��" << endl;
    for (int i = 0; i < p; i++)
        cout << pro[i] << "\t\t" << pro[i].GetTime() << endl;
}
void Admin::ShowAthlete()
{
    if (a == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    Sort_by_ID(ath);
    cout << "ID\t\t����\t�Ա�\tѧԺ" << endl;
    for (int i = 0; i < a; i++)
        cout << ath[i] <<"\t"<< ath[i].GetCollege() << endl;
}
//��Ϣ���
void Admin::AddCollege()
{
    string name;
    cout << "������ѧԺ����";
    cin >> name;//���Ʋ����ظ�
    if (FindCollege(name) == -1)//û�ҵ�
    {
        //ID�ÿ���ǰ��ID��ɾ�������
        for (int ID = 1; ID <= c + 1; ID++)//c+1��֤���������c����Ϊ��ʱcδ+1
        {
            if (FindCollege(to_string(ID)) == -1)//û�ҵ��Ǹ�ID
            {
                col[c].SetID(to_string(ID));
                break;
            }
        }
        col[c].SetName(name);
        c++;
        SaveCollege();//����һ������
        cout << "��ӳɹ���" << endl;
        enter_end();//���س�����
    }
    else
    {
        cout << "���Ʋ����ظ��������³��ԣ�" << endl;
        enter_end();
        AddCollege();
        return;
    }
}
void Admin::AddProject()
{
    string name;
    cout << "��������Ŀ����";
    cin >> name;
    if (FindProject(name) == -1)//û�ҵ�
    {
        //ID�ÿ���ǰ��ID��ɾ�������
        for (int ID = 1; ID <= p + 1; ID++)//��ʱp��δ+1
        {
            if (FindProject(to_string(ID)) == -1)//û�ҵ��Ǹ�ID
            {
                pro[p].SetID(to_string(ID));
                break;
            }
        }
        pro[p].SetName(name);
        cout << "��������Ŀ�ı���ʱ��(������ ʱ��)��";
        Date times;
        cin >> times;
        pro[p].SetTime(times);
        p++;
        SaveProject();//������Ŀ
        cout << "��ӳɹ���" << endl;
        enter_end();//�س�����
    }
    else
    {
        cout << "���Ʋ����ظ��������³��ԣ�" << endl;
        enter_end();
        AddProject();
        return;
    }
}
void Admin::AddAthlete()
{
    cout << "�������˶�ԱID���������Ա�(��/Ů)��ѧԺ(�ÿո��Tap���)" << endl;
    string ID, at_name, sex, col_name;
    cin >> ID >> at_name >> sex >> col_name;
    if (FindAthlete(ID) == -1)//û�ҵ�
    {
        //�����ӵ��û���ѧԺ�Ƿ����
        if (FindCollege(col_name) == -1)//û�ҵ���ѧԺ��
        {
            cout << "�������ѧԺ�����ڣ����������룡" << endl;
            enter_end();
            AddAthlete();
            return;
        }
        //���ڸ�ѧԺ
        ath[a].SetID(ID);
        ath[a].SetName(at_name);
        ath[a].SetSex((sex == "��" ? 1 : 0));
        ath[a].SetCollege(col_name);
        a++;
        SaveAthlete();//�����˶�Ա����
        cout << "��ӳɹ���" << endl;
        enter_end();
    }
    else
    {
        cout << "ID�����ظ��������³��ԣ�" << endl;
        enter_end();
        AddAthlete();
        return;
    }
}
//��Ϣɾ��
void Admin::RemoveCollege()
{
    if (c == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    ShowCollege();
    cout << "###ѧԺ��Ϣ��ɾ��###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  ѧԺ��" << endl;
    cout << "��ѡ����Ҫ���ҵ�ѡ�";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "��������Ҫɾ����ѧԺID��"; break;
    case 2:cout << "������Ҫɾ����ѧԺ���ƣ�"; break;
    default:
    {
        cout << "��������������������룡" << endl;
        enter_end();
        RemoveCollege();
        return;
    }
    }
    cin >> temp;
    if (FindCollege(temp) != -1)//�ҵ���
    {
        cout << "��ȷ����Ҫɾ����ѧԺΪ��";
        cout << col[FindCollege(temp)].GetName() << endl;
        for (int i = FindCollege(temp); i < c - 1; i++)
            col[i] = col[i + 1];
        c--;
        SaveCollege();
        cout << "ɾ���ɹ���" << endl;
    }
    else//û�ҵ�
        cout << "û���ҵ���" << endl;
    enter_end();
}
void Admin::RemoveProject()
{
    if (p == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    ShowProject();
    cout << "###��Ŀ��Ϣ��ɾ��###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  ��Ŀ��" << endl;
    cout << "��ѡ����Ҫ���ҵ�ѡ�";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "��������Ҫɾ������ĿID��"; break;
    case 2:cout << "������Ҫɾ������Ŀ���ƣ�"; break;
    default:
    {
        cout << "��������������������룡" << endl;
        enter_end();
        RemoveProject();
        return;
    }
    }
    cin >> temp;
    if (FindProject(temp) != -1)//�ҵ��˸���Ŀ��ID
    {
        cout << "��ȷ����Ҫɾ������ĿΪ��";
        cout << pro[FindProject(temp)].GetName() << endl;
        for (int i = FindProject(temp); i < p - 1; i++)
            pro[i] = pro[i + 1];
        p--;
        SaveProject();
        cout << "ɾ���ɹ���" << endl;
    }
    else
        cout << "û���ҵ���" << endl;
    enter_end();
}
void Admin::RemoveAthlete()
{
    if (a == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    ShowAthlete();
    cout << "###�˶�Ա��Ϣ��ɾ��###" << endl;
    string ID;
    cout << "��������Ҫɾ���˶�Ա��ID��";
    cin >> ID;
    if (FindAthlete(ID) != -1)//�ҵ��˸��˶�Ա��ID
    {
        cout << "��ȷ����Ҫɾ�����˶�ԱΪ��";
        cout << "ID��" << ath[FindAthlete(ID)].GetID() << "\t������" << ath[FindAthlete(ID)].GetName() << endl;
        for (int i = FindAthlete(ID); i < a - 1; i++)
            ath[i] = ath[i + 1];
        a--;
        SaveAthlete();
        cout << "ɾ���ɹ���" << endl;
    }
    else
        cout << "û���ҵ���ID��" << endl;
    enter_end();
}
//��Ϣ�޸�
void Admin::SetCollege()
{
    if (c == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    ShowCollege();
    cout << "###ѧԺ��Ϣ���޸�###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  ѧԺ��" << endl;
    cout << "��ѡ����Ҫ���ҵ�ѡ�";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "������Ŀ��ID��"; break;
    case 2:cout << "������Ŀ�����ƣ�"; break;
    default:
    {
        cout << "��������������������룡" << endl;
        enter_end();
        SetCollege();
        return;
    }
    }
    cin >> temp;
    if (FindCollege(temp) != -1)//�ҵ�
    {
        cout << "���ҵ���ѧԺ��ϢΪ��" << endl;
        cout << "ID\t\tѧԺ��" << endl;
        cout << col[FindCollege(temp)] << endl;
        string name;
        cout << "��������Ҫ�޸ĵ����ƣ�";
        cin >> name;
        //��������Ƿ��Ѿ�����
        if (FindCollege(name) != -1)//�ҵ�
        {
            cout << "�������ظ���" << endl;
            enter_end();
            return;
        }
        col[FindCollege(temp)].SetName(name);
        SaveCollege();
        cout << "�޸ĳɹ���" << endl;
        cout << "ID\tѧԺ��" << endl;
        cout << col[FindCollege(temp)] << endl;
    }
    else
        cout << "û���ҵ���" << endl;
    enter_end();
}
void Admin::SetProject()
{
    if (p == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    ShowProject();
    cout << "###��Ŀ��Ϣ���޸�###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  ��Ŀ��" << endl;
    cout << "��ѡ����Ҫ���ҵ�ѡ�";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "������Ŀ��ID��"; break;
    case 2:cout << "������Ŀ�����ƣ�"; break;
    default:
    {
        cout << "��������������������룡" << endl;
        enter_end();
        SetProject();
        return;
    }
    }
    cin >> temp;
    if (FindProject(temp) != -1)//�ҵ�
    {
        cout << "���ҵ�����Ŀ��ϢΪ��" << endl;
        cout << "ID\t\t��Ŀ��\tʱ��" << endl;
        cout << pro[FindProject(temp)] << pro[FindProject(temp)].GetTime() << endl;
        cout << "(1)��Ŀ��   (2)ʱ��" << endl;
        cout << "��������Ҫ�޸ĵ�ѡ�";
        int j;
        cin >> j;
        switch (j)
        {
        case 1:
        {
            string name;
            cout << "��������Ҫ�޸ĵ����ƣ�";
            cin >> name;
            //��������Ƿ��Ѿ�����
            if (FindProject(name) != -1)//�ҵ�
            {
                cout << "�������ظ���" << endl;
                enter_end();
                return;
            }
            pro[FindProject(temp)].SetName(name);
            break;
        }
        case 2:
        {
            Date time;
            cout << "��������Ҫ�޸ĵ�ʱ�䣺";
            cin >> time;
            pro[FindProject(temp)].SetTime(time);
            break;
        }
        default:
        {
            cout << "��������������������룡" << endl;
            enter_end();
            return;
        }
        }
        SaveProject();
        cout << "�޸ĳɹ���" << endl;
        cout << "ID\t\t��Ŀ��\tʱ��" << endl;
        cout << pro[FindProject(temp)] << pro[FindProject(temp)].GetTime() << endl;
    }
    else
        cout << "û���ҵ���" << endl;
    enter_end();
}
void Admin::SetAthlete()
{
    if (a == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    ShowAthlete();
    cout << "###�˶�Ա��Ϣ���޸�###" << endl;
    string ID;
    cout << "��������Ҫ�޸��˶�Ա��ID��";
    cin >> ID;
    if (FindAthlete(ID) != -1)//�ҵ��˸��˶�Ա��ID
    {
        int temp = FindAthlete(ID);
        cout << "���ҵ����˶�Ա��ϢΪ��" << endl;
        cout << "ID\t\t����\t�Ա�\tѧԺ" << endl;
        cout << ath[temp] << ath[temp].GetCollege() << endl;
        cout << "(1)����\t(2)�Ա�\t(3)ѧԺ" << endl;
        cout << "��������Ҫ�޸ĵ�ѡ�";
        int i;
        cin >> i;
        switch (i)
        {
        case 1://����
        {
            cout << "��������Ҫ�޸ĵ�������";
            string name;
            cin >> name;
            ath[temp].SetName(name);
            break;
        }
        case 2://�Ա�
        {
            cout << "��������Ҫ�޸ĵ��Ա�(��/Ů)��";
            string sex;
            cin >> sex;
            ath[temp].SetSex(sex == "��" ? 1 : 0);
            break;
        }
        case 3://ѧԺ
        {
            cout << "��������Ҫ�޸ĵ�ѧԺ��";
            string col_name;
            cin >> col_name;
            ath[temp].SetCollege(col_name);
            break;
        }
        default:
        {
            cout << "��������������������룡" << endl;
            enter_end();
            SetAthlete();
            return;
        }
        }
        SaveAthlete();
        cout << "�޸ĳɹ���" << endl;
        cout << "ID\t\t����\t�Ա�\tѧԺ" << endl;
        cout << ath[temp] << ath[temp].GetCollege() << endl;
    }
    else
        cout << "û���ҵ���ID��" << endl;
    enter_end();
}
//��Ϣ��ѯ
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
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    cout << "###ѧԺ��Ϣ�Ĳ���###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  ѧԺ��" << endl;
    cout << "��ѡ����Ҫ���ҵ�ѡ�";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1: cout << "������ѧԺID��"; break;
    case 2:cout << "������ѧԺ����"; break;
    default:
    {
        cout << "��������������������룡" << endl;
        enter_end();
        FindCollege();
        return;
    }
    }
    cin >> temp;
    if (FindCollege(temp) != -1)
    {
        cout << "�ҵ��˶�Ӧ " << temp << " �����ݣ�" << endl;
        cout << "ID\tѧԺ��" << endl;
        cout << col[FindCollege(temp)] << endl;
    }
    else
        cout << "û���ҵ���Ӧ " << temp << " �����ݣ�" << endl;
    enter_end();
}
void Admin::FindProject()
{
    if (p == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    cout << "###��Ŀ��Ϣ�Ĳ���###" << endl;
    cout << "(1)  ID" << endl;
    cout << "(2)  ��Ŀ��" << endl;
    cout << "��ѡ����Ҫ���ҵ�ѡ�";
    int i;
    cin >> i;
    string temp;
    switch (i)
    {
    case 1:cout << "��������ĿID��"; break;
    case 2:cout << "������ѧԺ����"; break;
    default:
    {
        cout << "��������������������룡" << endl;
        enter_end();
        FindProject();
        return;
    }
    }
    cin >> temp;
    if (FindProject(temp) != -1)
    {
        cout << "�ҵ��˶�Ӧ " << temp << " �����ݣ�" << endl;
        cout << "ID\t��Ŀ��" << endl;
        cout << pro[FindProject(temp)] << endl;
    }
    else
        cout << "û���ҵ���Ӧ " << temp << " �����ݣ�" << endl;
    enter_end();
}
void Admin::FindAthlete()
{
    if (a == 0)
    {
        cout << "û���κ����ݣ�" << endl;
        enter_end();
        return;
    }
    cout << "###�˶�Ա��Ϣ�Ĳ���###" << endl;
    cout << "�������˶�ԱID��";
    string ID;
    cin >> ID;
    if (FindAthlete(ID) != -1)
    {
        cout << "�ҵ��˶�Ӧ " << ID << " �����ݣ�" << endl;
        cout << "ID\t\t����\t�Ա�\tѧԺ" << endl;
        cout << ath[FindAthlete(ID)] << ath[FindAthlete(ID)].GetCollege() << endl;
    }
    else
        cout << "û���ҵ���Ӧ " << ID << " �����ݣ�" << endl;
    enter_end();
}
//��Ϣ����//ȫ����Ϣ����
void Admin::SaveCollege()
{
    ofstream ofile;
    ofile.open("sports_score_system/colleges.txt");
    ofile << "ID\t\tѧԺ��";
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
    ofile << "ID\t\t��Ŀ��\t\t����ʱ��";
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
    ofile << "ID\t\t\t����\t\t�Ա�\t\tѧԺ";
    Sort_by_ID(ath);
    for (int i = 0; i < a; i++)
    {
        ofile << endl << ath[i].GetID() << "\t" << ath[i].GetName() << "\t" << (ath[i].GetSex() == 0 ? "Ů" : "��") << "\t\t" << ath[i].GetCollege();
    }
    ofile.close();
}
void Admin::Save_apply_score()//���汨���������Ϣ(����ʱ������Ĭ��Ϊ0)
{
    ofstream ofile;
    ofile.open("sports_score_system/apply_score.txt");
    ofile << "UserID\t\t\tProjectID\t\tScore\tStr_Score";//����
    for (int i = 0; i < a; i++)//�����˶�Ա
    {
        if (ath[i].GetCount() > 0)//˵�����˶�Ա�б�����¼
        {
            for (int j = 0; j < ath[i].GetCount(); j++)
            {
                ofile << endl << ath[i].GetID() << "\t\t" << ath[i].GetProject(j).GetID() << "\t\t\t" << ath[i].GetProject(j).GetScore() << "\t\t" << ath[i].GetProject(j).GetStrScore();
            }
        }
    }
    ofile.close();
}
//��Ϣ��ȡ
void Admin::ReadCollege()
{
    if (_access("sports_score_system/colleges.txt", 0) != -1)//�ļ�����
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
    if (_access("sports_score_system/projects.txt", 0) != -1)//�ļ�����
    {
        ifstream ifile;
        ifile.open("sports_score_system/projects.txt");
        string line;
        getline(ifile, line);//��ű���
        Date times;//���ʱ��
        while (!ifile.eof())
        {
            ifile >> pro[p] >> times;
            pro[p].SetTime(times);//����ʱ��
            p++;
        }
        ifile.close();
    }
}
void Admin::ReadAthlete()
{
    if (_access("sports_score_system/athletes.txt", 0) != -1)//�ļ�����
    {
        ifstream ifile;
        ifile.open("sports_score_system/athletes.txt");
        string line;
        getline(ifile, line);//��ű���
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
void Admin::ReadApply()//��ȡ������Ϣ
{
    if (_access("sports_score_system/apply_score.txt", 0) != -1)//�ļ�����
    {
        ifstream ifile;
        ifile.open("sports_score_system/apply_score.txt");
        string line;//��ű���
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
//����
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
//����
int Admin::count_Athlete_sex(string pro_name, bool sex)//������Ŀ��Ů��������//0 Ů /1 ��
{
    //�����˶�Ա���ҳ���������Ŀ���ˣ��ж��Ա�
    int women_count = 0, man_count = 0;//Ů����������������
    for (int i = 0; i < a; i++)//�����˶�Ա
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
int Admin::count_Athlete_college(string pro_name, string col_name)//ͬϵ��������//��Ŀ/רҵ
{
    int count = 0;
    for (int i = 0; i < a; i++)
        if (ath[i].GetCollege()==col_name && ath[i].FindProject_ath(pro_name)!=-1)
            count++;
    return count;
}
int Admin::count_Athlete(string pro_name)//����ѧԺĳһ��Ŀ��������
{
    int count = 0;
    for (int i = 0; i < a; i++)
    {
        if (ath[i].FindProject_ath(pro_name) != -1)//�б�����Ŀ
            count++;
    }
    return count;
}
float Admin::sum_score(string col_name)//ѧԺ��//����ĳѧԺ���ܷ�
{
    float sum_score = 0;
    for (int i = 0; i < a; i++)
    {
        for(int j=0;j<ath[i].GetCount();j++)
        {
            float score = ath[i].GetProject(j).GetScore();
            if (ath[i].GetCollege() == col_name &&  score != 0)//ƥ�����ѧԺ��
            {
                sum_score += score;
            }
        }
    }
    return sum_score;
}