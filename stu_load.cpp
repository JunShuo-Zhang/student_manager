#include"student.h"
#include<iostream>
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

string old_under_id;
string old_post_id;
string post_id;
string under_id;

//将学生账号信息存入文件中
void stu_acc_manage::stu_acc_write() {
	ofstream outfile;
	outfile.open("under_account.txt", ios::out);
	if (!outfile) {
		cerr << "Error opening file : under_account.txt" << endl;
		system("pause");
		return;
	}
	outfile << stuList.size() << endl;
	for (int i = 0; i < stuList.size(); i++)
	{
		outfile << stuList[i].get_account() << " " << stuList[i].get_password() << endl;

	}
	outfile.close();
}

void stu_acc_manage::stu_acc_write(int i) {
	ofstream outfile;
	outfile.open("post_account.txt", ios::out);
	if (!outfile) {
		cerr << "Error opening file : post_account.txt" << endl;
		system("pause");
		return;
	}
	outfile << postacc_List.size() << endl;
	for (int i = 0; i < postacc_List.size(); i++)
	{
		outfile << postacc_List[i].get_account() << " " << postacc_List[i].get_password() << endl;

	}
	outfile.close();
}

//初始化学生账号
void stu_acc_manage::acc_init() {
	int n;
	ifstream infile;
	infile.open("under_account.txt", ios::in);
	if (!infile) {
		cerr << "Error opening file : under_account.txt" << endl;
		system("pause");
		return;
	}
	if (!(infile >> n)) {
		n = 0; // 文件为空或读取失败时将 n 设置为 0
	}
	string temp_account, temp_password;
	for (int i = 0; i < n; i++) {
		infile >> temp_account >> temp_password;
		stuList.push_back(stu_account(temp_account, temp_password));
	}
	infile.close();

	//初始化postacc
	infile.open("post_account.txt", ios::in);
	if (!infile) {
		cerr << "Error opening file : post_account.txt" << endl;
		system("pause");
		return;
	}
	if (!(infile >> n)) {
		n = 0; // 文件为空或读取失败时将 n 设置为 0
	}
	
	for (int i = 0; i < n; i++) {
		infile >> temp_account >> temp_password;
		postacc_List.push_back(stu_account(temp_account, temp_password));
	}
	infile.close();


}

//录入学生账号
void stu_acc_manage::stu_acc_in1() {
	string acc = post_id;
	string pass = "123456";
	postacc_List.emplace_back(acc, pass);
	stu_acc_write(0);
}

void stu_acc_manage::stu_acc_in2() {
	string acc = under_id;
	string pass = "123456";
	stuList.emplace_back(acc, pass);
	stu_acc_write();
}

//登录
int stu_acc_manage::stu_load_in() {
	if (stuList.size() == 0&& postacc_List.size() == 0) {
		cout << "\t\t\t\t   +--------------------+" << endl;
		cout << "\t\t\t\t   |  目前暂无可用账号  |" << endl;
		cout << "\t\t\t\t   +--------------------+" << endl;
		system("pause");
		return 0;
	}
	string choice1;
	while (true) {
		cout << "\t\t请根据您的情况选择：1.本科生  2.研究生:";
		cin >> choice1;
		if (choice1 == "1") {
			string account;
			cout << "\t\t\t请输入账号:";
			cin >> account;
			string password;
			cout << "\t\t\t请输入密码:";
			cin >> password;
			int flag = 0;
			for (int i = 0; i < stuList.size(); i++) {
				if (stuList[i].get_account() == account) {
					flag = 1;
					if (stuList[i].get_password() == password) {
						cout << "\t\t\t\t   +--------------------+" << endl;
						cout << "\t\t\t\t   |      登录成功      |" << endl;
						cout << "\t\t\t\t   +--------------------+" << endl;
						now = i;
						system("pause");
						return 1;
					}
					else {
						cout << "\t\t\t\t   +--------------------+" << endl;
						cout << "\t\t\t\t   |      密码错误      |" << endl;
						cout << "\t\t\t\t   +--------------------+" << endl;
						system("pause");
						return 0;
					}
				}
			}


			if (flag == 0) cout << "\t\t\t\t此账号还未注册！请先注册" << endl;
			system("pause");
			return 0;
			break;
		}


		else if (choice1 == "2") {
			string account;
			cout << "\t\t\t请输入账号:";
			cin >> account;
			string password;
			cout << "\t\t\t请输入密码:";
			cin >> password;
			int flag = 0;
			for (int i = 0; i < postacc_List.size(); i++) {
				if (postacc_List[i].get_account() == account) {
					flag = 1;
					if (postacc_List[i].get_password() == password) {
						cout << "\t\t\t\t   +--------------------+" << endl;
						cout << "\t\t\t\t   |      登录成功      |" << endl;
						cout << "\t\t\t\t   +--------------------+" << endl;
						now = i;
						system("pause");
						return 2;
					}
					else {
						cout << "\t\t\t\t   +--------------------+" << endl;
						cout << "\t\t\t\t   |      密码错误      |" << endl;
						cout << "\t\t\t\t   +--------------------+" << endl;
						system("pause");
						return 0;
					}
				}
			}


			if (flag == 0) cout << "\t\t\t\t此账号还未注册！请先注册" << endl;
			system("pause");
			return 0;
			break;
		}
		else {
			cout << "\t\t\t输入不合法,请重新选择【1-2】"<<endl;
		}
	}
}

//修改密码
void stu_acc_manage::change_pass(int now) {
	string  temp_password;
	cout << "\t\t\t请输入修改后的密码:";
	cin >> temp_password;
	stuList[now].update_password(temp_password);
	stu_acc_write();
	cout << "\t\t\t\t\t   +--------------------+" << endl;
	cout << "\t\t\t\t\t   |      修改成功      |" << endl;
	cout << "\t\t\t\t\t   +--------------------+" << endl;
	system("pause");
}

//清空学生账号
void stu_acc_manage::stu_clear() {
	stuList.clear();
	stu_acc_write();
}
void stu_acc_manage::stu_clear(int i) {
	postacc_List.clear();
	stu_acc_write(0);
}

//删除学生账号
void stu_acc_manage::stu_delete() {
	for (vector<stu_account>::iterator it = stuList.begin(); it != stuList.end(); ++it)
	{
		if (it->student_account == old_under_id) {
			stuList.erase(it);
			stu_acc_write();
			return;
		}
	}
}
void stu_acc_manage::stu_delete(int i) {
	for (vector<stu_account>::iterator it = postacc_List.begin(); it != postacc_List.end(); ++it)
	{
		if (it->student_account == old_post_id) {
			postacc_List.erase(it);
			stu_acc_write(0); 
			return;
		}
	}
}

//修改学生账号
void stu_acc_manage::acc_update()
{
	for (int i = 0; i < stuList.size(); i++)
	{
		if (stuList[i].get_account() == old_under_id) {
			stuList[i].update_account(under_id);
			stu_acc_write();
		}
	}
}
void stu_acc_manage::acc_update(int i)
{
	for (int i = 0; i < postacc_List.size(); i++)
	{
		if (postacc_List[i].get_account() == old_post_id) {
			postacc_List[i].update_account(post_id);
			stu_acc_write(0);
		}
	}
}