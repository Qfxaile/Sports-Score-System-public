#ifndef USERSUI_H
#define USERSUI_H
#include "users.h"
class UsersUI
{
	int c;//�û�����
	Users users[10];
	int GM;//�ж��Ƿ�Ϊ����Ա
public:
	UsersUI();//���ڳ�ʼ���û�����
	~UsersUI();//���ڽ���ʱ�Զ����򣬲��ҽ�ȫ�����ݴ�����ļ���
	int GetGM() { return GM; }//���ع���Ա״̬
	string GetID() { return users->GetUser(); }
	void menu();//����ִ��
	void main_menu();//���˵�
	void regist_menu();//ע��˵�
	void regist(int GM = 0);//ע��//trueΪ����Աע�ᣬfalseΪ��ͨ�û�ע��
	void login();//��¼//true����Ա��¼ falseΪ��ͨ�û���¼
	bool regist_enterpassword();//ע����������
	void login_enterpassword(string user);//��¼��������//�ж��Ƿ���ȷ
	int finduser(string user);//�ҵ��û�
	bool user_to_password(string user, string password);//�ж��û��������Ƿ�ƥ��
	void sort_by_user();//����ѧ��/���Ŵ�С�������ļ����ݸ�������
};
#endif // !USERSUI_H
