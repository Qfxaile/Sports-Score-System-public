#include "usersUI.h"
#include <exception>
#include "io.h"
#include <direct.h>
using namespace std;
bool login_state = false;//��¼ʧ��//���ڼ�¼�Ƿ��¼�ɹ�
UsersUI::UsersUI()//��ȡ�û����������Ҷ�ȡ�ļ��е����ݴ�����û�����
{
    c = 0;
    GM = -1;//Ĭ��û��ע��
    _mkdir("sports_score_system");
    if (_access("sports_score_system/users.txt", 0) != -1)//�ļ�����
    {
        ifstream ifile;
        ifile.open("sports_score_system/users.txt");

        string c1, c2, c3, c4;
        ifile >> c1 >> c2 >> c3 >> c4;//��ű���

        while (!ifile.eof())
        {
            ifile >> users[c++];
        }

        ifile.close();
    }
}
UsersUI::~UsersUI()
{
    if (c != 0)//�ж��Ƿ����û�ע��
    {
        sort_by_user();
        //ofile << endl;
        ofstream ofile;
        ofile.open("sports_score_system/users.txt");
        ofile << "�û���\t\t�˺�\t\t\t����\t\tGM";
        for (int i = 0; i < c; i++)
            ofile << endl << users[i];
        ofile.close();
    }
}
void UsersUI::menu()
{
    int n;
    for (;;)
    {
        main_menu();
        cin >> n;
        system("cls");
        switch (n)
        {
        case 1:
        {
            regist_menu();
            cin >> n;
            system("cls");
            switch (n)
            {
            case 1:regist(false); break;//�˶�Աע��
            case 2:regist(true); break;//����Աע��
            case 3:menu(); return;//������һ���˵�//reutn��ֹ�ݹ�
            case 4:cout << "��ӭʹ���˶���Ʒ�ϵͳ���ټ���"; return;//����
            default:break;
            }
        } break;//ע��
        case 2:login();break;//��½
        case 3:cout << "��ӭʹ���˶���Ʒ�ϵͳ���ټ���" << endl; return;//����
        default:break;
        }
        if (login_state == true)
            return;//��¼�ɹ�ֱ���˳�
    }
}
void UsersUI::main_menu()
{
    cout << "###��ӭʹ�ñ�ϵͳ###" << endl;
    cout << "(1)	�û�ע��" << endl;
    cout << "(2)	�û���¼" << endl;
    cout << "(3)	�˳�ϵͳ" << endl;
    cout << "��ѡ��";
}
void UsersUI::regist_menu()
{
    cout << "###�û�ע��###" << endl;
    cout << "(1)	�˶�Աע��" << endl;
    cout << "(2)	����Աע��" << endl;
    cout << "(3)	�����ϼ��˵�" << endl;
    cout << "(4)	�˳�ϵͳ" << endl;
    cout << "��ѡ��";
}
string password;//���ڴ������
void UsersUI::regist(int GM)//trueΪ����Աע�ᣬfalseΪ��ͨ�û�ע��
{
    string name, user;
    cout << "#####�û�ע��#####" << endl;

    //user
    cout << "����������ѧ��/���ţ�";
    cin >> user;
    if (finduser(user) == -1)//û���ظ����û�
    {
        //password
        bool f = false;
        while (true)
        {
            if (regist_enterpassword() == false)//���벻һ��
            {
                cout << "Warning:����������벻һ�£�" << endl;
                cout << "�Ƿ����������������ע�᣿(Y/N)��";
                char ch;
                cin >> ch;
                if (toupper(ch) == 'Y')
                    continue;
                else
                    break;
            }
            else//����һ��
            {
                f = true;
                break;
            }
        }//����������ע�� �������ȷ

        //name
        if (f == true)//ע��������������ƥ��
        {
            cout << "�����������û�����";
            cin >> name;
            cout << "�װ���" << name << "��ϲ��ע��ɹ���" << endl;

            //�����ݴ���user��
            //cout << c;
            users[c].Set(name, user, password, GM);
            //user���˽������ȷ����
            c++;//ע��ɹ��û�������һ

            //��ȡ���ݴ�ŵ��ļ�����
            ofstream ofile;
            ofile.open("sports_score_system/users.txt", ios::app);//append ׷�ӱ���
            ofile << endl << users[c - 1];
            ofile.close();


            cout << "�Ƿ������һ��"<<(GM==1?"����Ա":"�˶�Ա") << "��ע�᣿(Y/N)��";
            char ch;
            cin >> ch;
            if (toupper(ch) == 'Y')
                regist(GM);
            else
            {
                system("cls");
                menu();
            }
        }
    }
    else
    {
        cout << "ѧ��/�����ظ���������ע�ᣡ" << endl;
    }
}
void UsersUI::login()
{
    if (c == 0)
    {
        cout << "Warning�����в������κ��˺ţ���ע�ᣡ" << endl;
        menu();
        return;
    }
    password = "";
    string user;
    cout << "����������ѧ��/���ţ�";
    cin >> user;
    if (finduser(user) != -1)//�ҵ��˺�
    {
        login_enterpassword(user);//����
        return;
    }
    else
    {
        cout << "Warning�����в����ڸ��˺ţ���ע�ᣡ" << endl;
        menu();
        return;
    }
}
bool UsersUI::regist_enterpassword()
{
    password = "";
    cout << "�������������룺";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        password += ch;
        cout << '*';
    }
    cout << endl;
    cout << "���ٴ�ȷ�����룺";
    string temp = "";
    while ((ch = _getch()) != '\r')
    {
        temp += ch;
        cout << '*';
    }
    cout << endl;
    if (password == temp)
        return true;
    password = "";//���벻һ�¾����
    return false;
}
void UsersUI::login_enterpassword(string user)
{
    static int count = 1;//ͳ�������������
    password = "";
    cout << "�������������룺";
    //count++;//����+1
    char ch;
    while ((ch = _getch()) != '\r')
    {
        password += ch;
        cout << '*';
    }
    cout << endl;

    //�ж������Ƿ���ȷ
    if (user_to_password(user, password) == true)//�˺�����ƥ����ȷ
    {
        if (users[finduser(user)].GetGM() == true)//�ǹ���Ա
            GM = 1;
        else//���ǹ���Ա
            GM = 0;

        cout << "��¼�ɹ���" << endl;
        cout << "��ӭ" << (GM==1?"����Ա ":"�˶�Ա ") << users[finduser(user)].GetName() << " ��¼�˶���Ʒ�ϵͳ��" << endl;
        login_state = true;//������ȷ
    }
    else if (count++ < 3)//ƥ�䲻��ȷ//��������������������3��
    {
        //�����������롣����
        cout << "Warning��������󣡻�ʣ" << 4 - count << "�λ��ᣡ(��3�λ���)" << endl;
        login_enterpassword(user);
    }
    else
    {
        count = 0;
        cout << "Warning��������������Ѿ�����3�Σ���¼ʧ�ܣ�" << endl;
        login_state = false;//�������
    }
}
int UsersUI::finduser(string user)
{
    for (int i = 0; i < c; i++)
        if (users[i].GetUser() == user)
            return i;//�ҵ��û�
    return -1;//û���ҵ��û�
}
bool UsersUI::user_to_password(string user, string password)
{
    int i = finduser(user);//�ҵ��û�����λ��
    if (users[i].GetPassword() == password)//�ж��û���Ӧ���������������Ƿ���ͬ
        return true;//��ͬ
    return false;//����ͬ
}
void UsersUI::sort_by_user()
{
    //����
    for (int i = 0; i < c - 1; i++)
        for (int j = 0; j < c - 1 - i; j++)
            if (users[j].GetUser() > users[j + 1].GetUser())
                swap(users[j], users[j + 1]);
}