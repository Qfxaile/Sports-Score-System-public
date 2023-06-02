#include "usersUI.h"
#include <exception>
#include "io.h"
#include <direct.h>
using namespace std;
bool login_state = false;//登录失败//用于记录是否登录成功
UsersUI::UsersUI()//读取用户数量，并且读取文件中的数据存放入用户数组
{
    c = 0;
    GM = -1;//默认没有注册
    _mkdir("sports_score_system");
    if (_access("sports_score_system/users.txt", 0) != -1)//文件存在
    {
        ifstream ifile;
        ifile.open("sports_score_system/users.txt");

        string c1, c2, c3, c4;
        ifile >> c1 >> c2 >> c3 >> c4;//存放标题

        while (!ifile.eof())
        {
            ifile >> users[c++];
        }

        ifile.close();
    }
}
UsersUI::~UsersUI()
{
    if (c != 0)//判断是否有用户注册
    {
        sort_by_user();
        //ofile << endl;
        ofstream ofile;
        ofile.open("sports_score_system/users.txt");
        ofile << "用户名\t\t账号\t\t\t密码\t\tGM";
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
            case 1:regist(false); break;//运动员注册
            case 2:regist(true); break;//管理员注册
            case 3:menu(); return;//返回上一级菜单//reutn阻止递归
            case 4:cout << "欢迎使用运动会计分系统！再见！"; return;//结束
            default:break;
            }
        } break;//注册
        case 2:login();break;//登陆
        case 3:cout << "欢迎使用运动会计分系统！再见！" << endl; return;//结束
        default:break;
        }
        if (login_state == true)
            return;//登录成功直接退出
    }
}
void UsersUI::main_menu()
{
    cout << "###欢迎使用本系统###" << endl;
    cout << "(1)	用户注册" << endl;
    cout << "(2)	用户登录" << endl;
    cout << "(3)	退出系统" << endl;
    cout << "请选择：";
}
void UsersUI::regist_menu()
{
    cout << "###用户注册###" << endl;
    cout << "(1)	运动员注册" << endl;
    cout << "(2)	管理员注册" << endl;
    cout << "(3)	返回上级菜单" << endl;
    cout << "(4)	退出系统" << endl;
    cout << "请选择：";
}
string password;//用于存放密码
void UsersUI::regist(int GM)//true为管理员注册，false为普通用户注册
{
    string name, user;
    cout << "#####用户注册#####" << endl;

    //user
    cout << "请输入您的学号/工号：";
    cin >> user;
    if (finduser(user) == -1)//没有重复的用户
    {
        //password
        bool f = false;
        while (true)
        {
            if (regist_enterpassword() == false)//密码不一致
            {
                cout << "Warning:您输入的密码不一致！" << endl;
                cout << "是否重新输入密码继续注册？(Y/N)：";
                char ch;
                cin >> ch;
                if (toupper(ch) == 'Y')
                    continue;
                else
                    break;
            }
            else//密码一致
            {
                f = true;
                break;
            }
        }//结束代表不再注册 密码均正确

        //name
        if (f == true)//注册输入两次密码匹配
        {
            cout << "请输入您的用户名：";
            cin >> name;
            cout << "亲爱的" << name << "恭喜你注册成功！" << endl;

            //将数据传回user类
            //cout << c;
            users[c].Set(name, user, password, GM);
            //user类的私有数据确认了
            c++;//注册成功用户数量增一

            //获取数据存放到文件当中
            ofstream ofile;
            ofile.open("sports_score_system/users.txt", ios::app);//append 追加保存
            ofile << endl << users[c - 1];
            ofile.close();


            cout << "是否进行下一个"<<(GM==1?"管理员":"运动员") << "的注册？(Y/N)：";
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
        cout << "学号/工号重复！请重新注册！" << endl;
    }
}
void UsersUI::login()
{
    if (c == 0)
    {
        cout << "Warning：库中不存在任何账号，请注册！" << endl;
        menu();
        return;
    }
    password = "";
    string user;
    cout << "请输入您的学号/工号：";
    cin >> user;
    if (finduser(user) != -1)//找到账号
    {
        login_enterpassword(user);//密码
        return;
    }
    else
    {
        cout << "Warning：库中不存在该账号，请注册！" << endl;
        menu();
        return;
    }
}
bool UsersUI::regist_enterpassword()
{
    password = "";
    cout << "请输入您的密码：";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        password += ch;
        cout << '*';
    }
    cout << endl;
    cout << "请再次确认密码：";
    string temp = "";
    while ((ch = _getch()) != '\r')
    {
        temp += ch;
        cout << '*';
    }
    cout << endl;
    if (password == temp)
        return true;
    password = "";//密码不一致就清空
    return false;
}
void UsersUI::login_enterpassword(string user)
{
    static int count = 1;//统计密码输入次数
    password = "";
    cout << "请输入您的密码：";
    //count++;//次数+1
    char ch;
    while ((ch = _getch()) != '\r')
    {
        password += ch;
        cout << '*';
    }
    cout << endl;

    //判断密码是否正确
    if (user_to_password(user, password) == true)//账号密码匹配正确
    {
        if (users[finduser(user)].GetGM() == true)//是管理员
            GM = 1;
        else//不是管理员
            GM = 0;

        cout << "登录成功！" << endl;
        cout << "欢迎" << (GM==1?"管理员 ":"运动员 ") << users[finduser(user)].GetName() << " 登录运动会计分系统！" << endl;
        login_state = true;//密码正确
    }
    else if (count++ < 3)//匹配不正确//输入密码错误次数不超过3次
    {
        //重新输入密码。。。
        cout << "Warning：密码错误！还剩" << 4 - count << "次机会！(共3次机会)" << endl;
        login_enterpassword(user);
    }
    else
    {
        count = 0;
        cout << "Warning：输入密码次数已经超出3次！登录失败！" << endl;
        login_state = false;//密码错误
    }
}
int UsersUI::finduser(string user)
{
    for (int i = 0; i < c; i++)
        if (users[i].GetUser() == user)
            return i;//找到用户
    return -1;//没有找到用户
}
bool UsersUI::user_to_password(string user, string password)
{
    int i = finduser(user);//找到用户所在位置
    if (users[i].GetPassword() == password)//判断用户对应密码与输入密码是否相同
        return true;//相同
    return false;//不相同
}
void UsersUI::sort_by_user()
{
    //排序
    for (int i = 0; i < c - 1; i++)
        for (int j = 0; j < c - 1 - i; j++)
            if (users[j].GetUser() > users[j + 1].GetUser())
                swap(users[j], users[j + 1]);
}