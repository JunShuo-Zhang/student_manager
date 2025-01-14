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
	string subject;  //学科
	double score;  //成绩
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
	string classNo;  //班级
	vector<subject_score> stu_score;  //学生各科成绩信息
	int sub_num;  //科目数
	double ave_score;  //平均分

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

	void under_init();  //初始化
	void under_menu();  //主菜单
	void under_writefile();  //将本科生信息写入到文件中
	void under_create();  //录入本科生信息
	void under_display();  //展示本科生信息
	void under_base_display(undergraduate);  //展示某一本科生基本信息
	void under_score_display(undergraduate);  //展示某一本科生成绩信息
	void under_example();  //本科生基本信息一览表
	void under_delete();  //删除本科生信息
	void under_update();  //修改本科生信息
	void under_find();//查询本科生信息
	void under_clear();//清空本科生数据
	void under_sort();//统计本科生数据(排序)
	void under_stuChart();//学生信息速览表
	void under_display_one(int);  //展示一位同学的信息
	static string show_id();
};


