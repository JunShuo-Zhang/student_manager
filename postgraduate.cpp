#include "postgraduate.h"
#include<iostream>
#include<vector>
#include <fstream>
#include<iomanip>
#include<algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::left;
using std::setw;
using std::vector;


//研究生基本信息一览表
void post_manager::post_example()
{
	cout << "\t\t示例：" << endl;
	cout << "\t--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t学号\t姓名\t性别\t出生日期\t专业\t电话\t\t邮箱\t\t\t课题\t\t导师" << endl;
	cout << "\t2023001\t李四\t男\t2000-12-12\t物理\t98765432101\tlisi@example.com\t量子计算\t王教授" << endl;
	cout << "\t--------------------------------------------------------------------------------------------------------------" << endl;
}

//研究生信息初始化
void post_manager::post_init()
{
	// 读取研究生信息
	ifstream in_postFile("postgraduate_information.txt");
	if (!in_postFile) {
		cout << "Failed to open postgraduate_information.txt" << endl;
		return;
	}

	int postCount;
	if (!(in_postFile >> postCount)) {
		postCount = 0; // 文件为空或读取失败时将 n 设置为 0
	}
	in_postFile.ignore(); // 跳过换行符

	for (int i = 0; i < postCount; ++i) {
		string id, name,gender, year, month, day, major, phone_num, email, title, tutor;

		in_postFile >> id >> name >> gender >> year >> month >> day >> major >> phone_num >> email >> title >> tutor;

		postList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, title, tutor);
	}

	in_postFile.close();
}

//研究生信息管理主菜单
void post_manager::post_menu()
{
	string choice = "0";
	system("cls");
	cout << "\n\n\t\t\t*******************欢迎来到研究生信息管理系统********************" << endl;
	cout << "\t\t\t你可以进行以下操作:" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        1   添加研究生信息      |     2   删除研究生信息         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        3   修改研究生信息      |     4   查询研究生信息         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        5   清空研究生数据      |     6   统计研究生数据(排序)   |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        7   展示研究生信息      |     0   返回学生管理系统       |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t请选择【0-7】：";
	cin >> choice;
	while (choice != "0" && choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7")
	{
		cout << "\t\t\t输入不合法,请重新选择【0-8】：";
		cin >> choice;
	}
	if (choice == "1")
	{
		this->post_create();
		this->post_menu();
	}
	else if (choice == "2")
	{
		this->post_delete();
		this->post_menu();
	}
	else if (choice == "3")
	{
		this->post_update();
		this->post_menu();
	}
	else if (choice == "4")
	{
		this->post_find();
		this->post_menu();
	}
	else if (choice == "5")
	{
		this->post_clear();
		this->post_menu();
	}
	else if (choice == "6")
	{
		this->post_sort();
		this->post_menu();
	}
	else if (choice == "7")
	{
		this->post_display();
		this->post_menu();
	}
	else if (choice == "0")
	{
		return;
	}
}

//将研究生信息写入到文件中
void post_manager::post_writefile()
{
	ofstream outfile;
	outfile.open("postgraduate_information.txt", ios::out);
	if (!outfile) {
		cerr << "Error opening file : postgraduate_information.txt" << endl;
		return;
	}
	outfile << postList.size() << endl;
	for (int i = 0; i < postList.size(); i++)
	{
		outfile << postList[i].id << " " << postList[i].name << " " <<postList[i].gender << " "
			<< postList[i].data_of_birth.get_year() << " " << postList[i].data_of_birth.get_month() << " "
			<< postList[i].data_of_birth.get_day() << " "
			<< postList[i].major << " " << postList[i].phone_num << " " << postList[i].email << " "
			<< postList[i].title << " " << postList[i].tutor << endl;
	}
	outfile.close();
}

//研究生信息录入
void post_manager::post_create()
{
	while (true) {
		system("cls");
		cout << "\t\t**********************欢迎来到研究生信息添加功能*************************" << endl;
		cout << "\t\t研究生基本信息一览表：" << endl;
		post_example();
		cout << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t1 添加研究生信息" << endl;
		cout << "\t\t0 返回主菜单" << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t请选择【0-1】：";
		string choice;
		cin >> choice;
		while (choice != "1" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新输入【0-1】：";
			cin >> choice;
		}
		if (choice == "1") {
			string flag = "1";
			while (flag == "1")
			{
				string id, name,gender, year, month, day, major, phone_num, email, title, tutor;
				cout << "\t\t输入研究生信息：" << endl;
				cout << "\t\t请输入学号：";
				bool check = false;
				do
				{
					check = false;
					cin >> id;
					for (int i = 0; i < postList.size(); ++i)
					{
						if (id == postList[i].id)
						{
							cout << "\t\t该学号已存在，请重新输入：";
							check = true;
						}
					}
				} while (check);
				cout << "\t\t请输入姓名：";
				cin >> name;
				while (1) {
					cout << "\t\t请输入性别：";
					cin >> gender;
					if (gender != "男" && gender != "女")
						cout << "\t\t输入不合法,请重新输入：";
					else break;

				}
				cout << "\t\t请输入出生年份：";
				cin >> year;
				cout << "\t\t请输入出生月份：";
				cin >> month;
				cout << "\t\t请输入出生日：";
				cin >> day;
				cout << "\t\t请输入专业：";
				cin >> major;
				cout << "\t\t请输入电话号码：";
				cin >> phone_num;
				cout << "\t\t请输入电子邮箱：";
				cin >> email;
				cout << "\t\t请输入研究课题：";
				cin >> title;
				cout << "\t\t请输入导师姓名：";
				cin >> tutor;
				postList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, title, tutor);
				post_writefile();
				post_id = id;
				accountSystem.stu_acc_in1();

				cout << "\n\t\t该研究生信息添加成功！是否继续添加？（1 是 0 否）" << endl;
				cout << "\t\t请进行选择【0-1】：";
				cin >> flag;
				while (flag != "0" && flag != "1")
				{
					cout << "\t\t输入不合法,请重新选择【0-1】：";
					cin >> flag;
				}
				if (flag == "0") {
					return;
				}
			}
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "0") {
			break;
		}
	}
}

//研究生信息删除功能
void post_manager::post_delete()
{
	system("cls");
	cout << "\t\t**********************删除研究生信息*************************" << endl;
	cout << "\t\t请输入要删除的研究生学号：";
	string id;
	cin >> id;

	auto it = std::find_if(postList.begin(), postList.end(), [&](postgraduate& p)
	{
		return p.id == id;
	});

	if (it != postList.end()) {
		old_post_id = it->id;
		postList.erase(it);
		post_writefile();
		accountSystem.stu_delete(0);
		cout << "\t\t研究生信息删除成功！" << endl;
	}
	else {
		cout << "\t\t没有找到该学号的研究生信息！" << endl;
	}

	system("pause");
}

//研究生信息修改功能
void post_manager::post_update()
{
	system("cls");
	cout << "\t\t**********************修改研究生信息*************************" << endl;
	cout << "\t\t请输入要修改信息的研究生学号：";
	string id;
	cin >> id;

	auto it = std::find_if(postList.begin(), postList.end(), [&](postgraduate& p) {
		return p.id == id;
		});

	if (it != postList.end()) {	
		cout << "\t\t找到研究生信息：" << endl;
		cout << "\t\t学号：" << it->id << endl;
		cout << "\t\t姓名：" << it->name << endl;
		cout << "\t\t出生日期：" << it->data_of_birth.get_year() << "-" << it->data_of_birth.get_month() << "-" << it->data_of_birth.get_day() << endl;
		cout << "\t\t专业：" << it->major << endl;
		cout << "\t\t电话：" << it->phone_num << endl;
		cout << "\t\t邮箱：" << it->email << endl;
		cout << "\t\t课题：" << it->title << endl;
		cout << "\t\t导师：" << it->tutor << endl;

		while (true)
		{
			cout << "\t\t请选择要修改的信息：" << endl;
			cout << "\t\t1 学号  2. 姓名  3. 性别  4. 出生日期  5. 专业  6. 电话  7. 邮箱  8. 课题  9. 导师" << endl;
			cout << "\t\t请输入选择【0-8】:";
			int choice;
			cin >> choice;

			string input;
			string year, month, day;
			switch (choice) {
			case 1:
				old_post_id = it->id;
				cout << "\t\t请输入新的学号：";
				cin >> input;
				it->id = input;
				post_id = it->id;
				accountSystem.acc_update(0);
				break;
				
			case 2:
				cout << "\t\t请输入新的姓名：";
				cin >> input;
				it->name = input;
				break;
			case 3:
				cout << "\t\t请输入新的性别：";
				cin >> input;
				it->gender = input;
				break;
			case 4:
				cout << "\t\t请输入新的出生年份：";
				cin >> year;
				cout << "\t\t请输入新的出生月份：";
				cin >> month;
				cout << "\t\t请输入新的出生日期：";
				cin >> day;
				it->change_birth(year, month, day);
				break;
			case 5:
				cout << "\t\t请输入新的专业：";
				cin >> input;
				it->major = input;
				break;
			case 6:
				cout << "\t\t请输入新的电话：";
				cin >> input;
				it->phone_num = input;
				break;
			case 7:
				cout << "\t\t请输入新的邮箱：";
				cin >> input;
				it->email = input;
				break;
			case 8:
				cout << "\t\t请输入新的课题：";
				cin >> input;
				it->title = input;
				break;
			case 9:
				cout << "\t\t请输入新的导师：";
				cin >> input;
				it->tutor = input;
				break;
			default:
				cout << "\t\t无效选择！" << endl;
				break;
			}
			post_writefile();
			string option;
			cout << "\t\t该信息修改成功！是否继续修改？（1 是 0 否）" << endl;
			cout << "\t\t请进行选择【0-1】：";
			cin >> option;
			while (option != "0" && option != "1")
			{
				cout << "\t\t输入不合法,请重新选择【0-1】：";
				cin >> option;
			}
			if (option == "0"){
				break;
			}
			else if (option == "1") {
				continue;
			}
		}
	}
	else {
		cout << "\t\t没有找到该学号的研究生信息！" << endl;
	}
	system("pause");
}

//研究生信息查询功能
void post_manager::post_find()
{
	system("cls");
	cout << "\t\t**********************查询研究生信息*************************" << endl;
	cout << "\t\t请输入要查询的研究生学号：";
	string id;
	cin >> id;

	// 通过学号查询
	auto it = std::find_if(postList.begin(), postList.end(), [&](postgraduate& p) {
		return p.id == id;
		});

	if (it != postList.end()) {
		cout << "\t\t学号：" << it->id << endl;
		cout << "\t\t姓名：" << it->name << endl;
		cout << "\t\t性别：" << it->gender << endl;
		cout << "\t\t出生日期：" << it->data_of_birth.get_year() << "-" << it->data_of_birth.get_month() << "-" << it->data_of_birth.get_day() << endl;
		cout << "\t\t专业：" << it->major << endl;
		cout << "\t\t电话：" << it->phone_num<< endl;
		cout << "\t\t邮箱：" << it->email << endl;
		cout << "\t\t课题：" << it->title << endl;
		cout << "\t\t导师：" << it->tutor << endl;
	}
	else {
		cout << "\t\t没有找到该学号的研究生信息！" << endl;
	}
	system("pause");
}

//研究生信息清空功能
void post_manager::post_clear()
{
	system("cls");
	cout << "\t\t**********************清空所有研究生信息*************************" << endl;
	cout << "\t\t你确定要清空所有研究生数据吗？（1 是 0 否）:";
	string choice;
	cin >> choice;

	if (choice == "1") {
		postList.clear();
		post_writefile();
		accountSystem.stu_clear(0);
		cout << "\t\t所有研究生信息已成功清空！" << endl;
	}
	else {
		cout << "\t\t操作已取消！" << endl;
	}
	system("pause");
}

//研究生信息统计（排序）功能
void post_manager::post_sort()
{
	system("cls");
	cout << "\t\t**********************统计研究生数据(排序)*************************" << endl;
	cout << "\t\t请选择排序方式：" << endl;
	cout << "\t\t1. 按学号排序" << endl;
	cout << "\t\t2. 按姓名排序" << endl;
	cout << "\t\t请输入选择【1-2】:";
	string choice;
	cin >> choice;

	if (choice == "1") {
		// 通过学号排序
		std::sort(postList.begin(), postList.end(), [](postgraduate& a, postgraduate& b) {
			return a.id < b.id;
			});
		cout << "\t\t按学号升序排列如下：" << endl;
		post_stuChart();

	}
	else if (choice == "2") {
		// 通过姓名排序
		std::sort(postList.begin(), postList.end(), [](postgraduate& a, postgraduate& b) {
			return a.name < b.name;
			});
		cout << "\t\t按姓名首字母排序如下：" << endl;
		post_stuChart();
	}
	else {
		cout << "\t\t无效选择！" << endl;
	}
	post_writefile();
	system("pause");
}

//展示一位同学的信息
void post_manager::post_display_one(int i)
{
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << "学号";
	cout << left << setw(10) << "姓名";
	cout << left << setw(5) << "性别";
	cout << left << setw(20) << "专业";
	cout << left << setw(15) << "研究课题";
	cout << left << setw(10) << "导师姓名";
	cout << left << setw(15) << "电话号码";
	cout << left << setw(18) << "电子邮箱";
	cout << left << setw(15) << "出生日期";
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << postList[i].get_id();
	cout << left << setw(10) << postList[i].name;
	cout << left << setw(5) << postList[i].gender;
	cout << left << setw(20) << postList[i].major;
	cout << left << setw(15) << postList[i].title;
	cout << left << setw(10) << postList[i].tutor;
	cout << left << setw(15) << postList[i].phone_num;
	cout << left << setw(18) << postList[i].email;
	cout << left << postList[i].data_of_birth.get_year() << "-" << postList[i].data_of_birth.get_month() << "-" << postList[i].data_of_birth.get_day();
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	system("pause");
}

//研究生信息展示功能
void post_manager::post_display()
{
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << "学号";
	cout << left << setw(10) << "姓名";
	cout << left << setw(5) << "性别";
	cout << left << setw(20) << "专业";
	cout << left << setw(15) << "研究课题";
	cout << left << setw(10) << "导师姓名";
	cout << left << setw(15) << "电话号码";
	cout << left << setw(18) << "电子邮箱";
	cout << left << setw(15) << "出生日期";
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < postList.size(); i++)
	{
		cout << left << setw(15) << postList[i].get_id();
		cout << left << setw(10) << postList[i].name;
		cout << left << setw(5) << postList[i].gender;
		cout << left << setw(20) << postList[i].major;
		cout << left << setw(15) << postList[i].title;
		cout << left << setw(10) << postList[i].tutor;
		cout << left << setw(15) << postList[i].phone_num;
		cout << left << setw(18) << postList[i].email;
		cout << left << postList[i].data_of_birth.get_year() << "-" << postList[i].data_of_birth.get_month() << "-" << postList[i].data_of_birth.get_day();
		cout << endl;
	}
	if (postList.size() == 0) cout << "\t\t\t\t\t\t当前暂无学生\n";
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	system("pause");
}

//学生信息速览
void post_manager::post_stuChart() {

	cout << "\t\t---------------------------------------------------------------------------------" << endl;
	cout << "\t\t";
	cout << left << setw(15) << "学号";
	cout << left << setw(10) << "姓名";
	cout << left << setw(5) << "性别";
	cout << left << setw(20) << "专业";
	cout << left << setw(20) << "研究课题";
	cout << left << setw(10) << "导师姓名" << endl;
	cout << "\t\t---------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < postList.size(); i++) {
		cout << "\t\t";
		cout << left << setw(15) << postList[i].get_id();
		cout << left << setw(10) << postList[i].name;
		cout << left << setw(5) << postList[i].gender;
		cout << left << setw(20) << postList[i].major;
		cout << left << setw(20) << postList[i].title;
		cout << left << setw(10) << postList[i].tutor << endl;
	}
	if (postList.empty()) cout << "\t\t\t\t\t\t当前暂无学生哦~\n";
	cout << "\t\t---------------------------------------------------------------------------------" << endl;



}
