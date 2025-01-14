#pragma once
#include"stu_load.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::string;
using std::vector;

extern stu_acc_manage accountSystem;

class data
{
protected:
	string year;
	string month;
	string day;
public:
	data() {}
	data(string _year, string _month, string _day)
		:year(_year), month(_month), day(_day) {}
	~data() {}
	inline string get_year() {
		return year;
	}
	inline string get_month() {
		return month;
	}
	inline string get_day() {
		return day;
	}
	inline void change_year(string year)
	{
		this -> year = year;
	}
	inline void change_month(string month)
	{
		this->month = month;
	}
	inline void change_day(string day)
	{
		this->day = day;
	}
};
class student
{
protected:
	string id;  //学号
	string name;  //姓名
	string gender;  //性别
	data data_of_birth;  //出生日期
	string major;  //专业
	string phone_num;  //电话号码
	string email;  //邮箱
public:
	student() {}
	student(string _id, string _name,string _gender, string _year, string _month, string _day, string _major, string _phone_num, string _email)
		:id(_id), name(_name),gender(_gender), data_of_birth(_year, _month, _day), major(_major), phone_num(_phone_num), email(_email) {}
	~student() {};
	void change_birth(string year, string month, string day)
	{
		data_of_birth.change_year(year);
		data_of_birth.change_month(month);
		data_of_birth.change_day(day);
	}
	
	string get_id()
	{
		return id;
	}
};
