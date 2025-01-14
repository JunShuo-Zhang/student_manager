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
	string title;  //研究课题
	string tutor;  //导师姓名
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

	void post_init();  //初始化
	void post_menu();  //主菜单
	void post_writefile();  //将研究生信息写入到文件中
	void post_create();  //录入研究生信息
	void post_display();  //展示研究生信息
	void post_example();  //研究生基本信息一览表
	void post_delete();  //删除研究生信息
	void post_update();  //修改研究生信息
	void post_find();//查询研究生信息
	void post_clear();//清空研究生数据
	void post_sort();//统计研究生数据(排序)
	void post_stuChart();  //学生信息速览
	void post_display_one(int); //展示一位同学的信息
};



