#pragma once
#include"student.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::string;
using std::vector;

class subject_score
{
private:
	string subject;  //ѧ��
	double score;  //�ɼ�
public:
	subject_score() {}
	subject_score(string _subject, double _score)
		:subject(_subject), score(_score) {}
	~subject_score() {}
	inline string get_subject()
	{
		return subject;
	}
	inline double get_score()
	{
		return score;
	}
	inline void change_subject(string sub)
	{
		this->subject = sub;
	}
	inline void change_score(double sco)
	{
		this->score = sco;
	}
};

typedef struct {
	string number;
	string sub_name;
}all_subject;

class undergraduate :public student
{
	friend class under_manager;
private:
	string classNo;  //�༶
	vector<subject_score> stu_score;  //ѧ�����Ƴɼ���Ϣ
	int sub_num;  //��Ŀ��
	double ave_score;  //ƽ����

public:
	undergraduate() {}
	undergraduate(string _id, string _name, string _gender, string _year, string _month, string _day, string _major, string _phone_num, string _email,
		string _classNo, vector<subject_score> _stu_score, int _sub_num, double _ave_score)
		:student(_id, _name,_gender, _year, _month, _day, _major, _phone_num, _email), classNo(_classNo), stu_score(_stu_score), sub_num(_sub_num), ave_score(_ave_score)
	{
		
	}
	~undergraduate() {};
	double get_ave()
	{
		return ave_score;
	}
};

class under_manager:public undergraduate
{
	friend class stu_acc_manage;
protected:
	vector<undergraduate> underList;
	vector<all_subject> All_sub;
public:
	under_manager() {}
	under_manager(vector<undergraduate> _underList) : underList(_underList) {}
	~under_manager() {}

	void under_init();  //��ʼ��
	void under_menu();  //���˵�
	void under_writefile();  //����������Ϣд�뵽�ļ���
	void under_create();  //¼�뱾������Ϣ
	void under_display();  //չʾ��������Ϣ
	void under_base_display(undergraduate);  //չʾĳһ������������Ϣ
	void under_score_display(undergraduate);  //չʾĳһ�������ɼ���Ϣ
	void under_example();  //������������Ϣһ����
	void under_delete();  //ɾ����������Ϣ
	void under_update();  //�޸ı�������Ϣ
	void under_find();//��ѯ��������Ϣ
	void under_clear();//��ձ���������
	void under_sort();//ͳ�Ʊ���������(����)
	void under_stuChart();//ѧ����Ϣ������
	void under_display_one(int);  //չʾһλͬѧ����Ϣ
	static string show_id();
};


