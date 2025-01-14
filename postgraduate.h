#pragma once
#include"student.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::string;
using std::vector;

class postgraduate :public student
{
	friend class post_manager;
protected:
	string title;  //�о�����
	string tutor;  //��ʦ����
public:
	postgraduate() {}
	postgraduate(string _id, string _name,string _gender, string _year, string _month, string _day, string _major, string _phone_num, string _email, string _title, string _tutor)
		:student(_id, _name,_gender, _year, _month, _day, _major, _phone_num, _email), title(_title), tutor(_tutor) {}
	~postgraduate() {};
};

class post_manager
{
	friend class stu_acc_manage;
private:
	vector<postgraduate> postList;
public:
	post_manager() {}
	post_manager(vector<postgraduate> _postList) : postList(_postList) {}
	~post_manager() {}

	void post_init();  //��ʼ��
	void post_menu();  //���˵�
	void post_writefile();  //���о�����Ϣд�뵽�ļ���
	void post_create();  //¼���о�����Ϣ
	void post_display();  //չʾ�о�����Ϣ
	void post_example();  //�о���������Ϣһ����
	void post_delete();  //ɾ���о�����Ϣ
	void post_update();  //�޸��о�����Ϣ
	void post_find();//��ѯ�о�����Ϣ
	void post_clear();//����о�������
	void post_sort();//ͳ���о�������(����)
	void post_stuChart();  //ѧ����Ϣ����
	void post_display_one(int); //չʾһλͬѧ����Ϣ
};



