#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ostream;

static int now;

extern string old_under_id;
extern string old_post_id;
extern string post_id;
extern string under_id;


class stu_account 
{
	friend class stu_acc_manage;
protected:
	string student_account;
	string student_password;
public:
	stu_account() {}
	stu_account(string stu_acc, string stu_pass) : student_account(stu_acc), student_password(stu_pass) {}
	~stu_account() {}
	string get_account()
	{
		return student_account;
	}
	string get_password()
	{
		return student_password;
	}
	void update_account(string new_account)
	{
		this->student_account = new_account;
	}
	void update_password(string new_password)
	{
		this->student_password = new_password;
	}
};

class stu_acc_manage :public stu_account {
	
protected:
	vector<stu_account> stuList;
	vector<stu_account> postacc_List;
public:
	stu_acc_manage() {}
	stu_acc_manage(vector<stu_account> _stuList) :stuList(_stuList) {}
	~stu_acc_manage() {}
	void stu_acc_in1();//¼��ѧ���˺�
	void stu_acc_in2();
	void stu_acc_write();//��ѧ����Ϣд���ļ�
	void stu_acc_write(int i);//�������� ����under��post ,post������������0
	void acc_init();//��ʼ��ѧ���˺���Ϣ
	int stu_load_in();//��¼
	void change_pass(int);//�޸�����
	//ɾ��ѧ���˺�
	void stu_delete();
	void stu_delete(int i);
	//���ѧ���˺�
	void stu_clear();
	void stu_clear(int i);
	//�޸�ѧ���˺�
	void acc_update();
	void acc_update(int);
};