#include"undergraduate.h"
#include"postgraduate.h"
#include<iostream>
#include <fstream>
#include<iomanip>
#include<algorithm>
#include<string>

#define admin_account "account"
#define admin_password "password"

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

int main()
{
	under_manager underSystem;
	post_manager postSystem;

	underSystem.under_init();
	postSystem.post_init();
	accountSystem.acc_init();

	string account, password;
	while (true) {
		
		string choice = "2";;
		
		system("cls");
		cout << "\t\t+-------------------------------------------------------+\n";
		cout << "\t\t|                  1、学生登录                          |\n";
		cout << "\t\t|          (账号为学号，初始密码为123456）              |\n";
		cout << "\t\t+-------------------------------------------------------+\n";
		cout << "\t\t|                  2、管理员登录                        |\n";
		cout << "\t\t+-------------------------------------------------------+\n";
		cout << "\t\t|                  0、退出系统                          |\n";
		cout << "\t\t+-------------------------------------------------------+\n";
		cout << "\t\t请输入:";
		cin >> choice;
		
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t\t输入不合法,请重新选择【0-2】：";
			cin >> choice;
		}
		if (choice == "2")
		{
			int flag = 1;
			while (flag) {
				
				string account;
				cout << "\t\t\t请输入账号:";
				cin >> account;
				string password;
				cout << "\t\t\t请输入密码:";
				cin >> password;
				
				if (account == admin_account && password == admin_password) {
					cout << "\t\t\t\t   +--------------------+" << endl;
					cout << "\t\t\t\t   |      登录成功      |" << endl;
					cout << "\t\t\t\t   +--------------------+" << endl;
					system("pause");
					
					while (true) {
						system("cls");
						string choice = "0";
						cout << "\n\n\t\t\t*******************欢迎来到学生信息管理系统********************" << endl;
						cout << "\t\t\t你可以进行以下操作:" << endl;
						cout << "\t\t\t|-------------------------------------------------------------|" << endl;
						cout << "\t\t\t|              1   进入本科生信息管理系统                     |" << endl;
						cout << "\t\t\t|-------------------------------------------------------------|" << endl;
						cout << "\t\t\t|              2   进入研究生信息管理系统                     |" << endl;
						cout << "\t\t\t|-------------------------------------------------------------|" << endl;
						cout << "\t\t\t|              3   返回初始页面                               |" << endl;
						cout << "\t\t\t|-------------------------------------------------------------|" << endl;
						cout << "\t\t\t|              0   退出系统                                   |" << endl;
						cout << "\t\t\t|-------------------------------------------------------------|" << endl;
						cout << "\t\t\t请选择【0-3】：";
						cin >> choice;
						while (choice != "0" && choice != "1" && choice != "2" && choice != "3")
						{
							cout << "\t\t\t输入不合法,请重新选择【0-3】：";
							cin >> choice;
						}
						if (choice == "1")
						{
							underSystem.under_menu();
							continue;
						}
						else if (choice == "2")
						{
							postSystem.post_menu();
							continue;
						}
						else if (choice == "3")
						{
							flag = 0;
							break;
						}
						else if (choice == "0")
						{
							exit(0);
						}
					}

				}
				else if (account != admin_account) {
					cout << "\t\t\t\t   +--------------------+" << endl;
					cout << "\t\t\t\t   |      账号错误      |" << endl;
					cout << "\t\t\t\t   +--------------------+" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "\t\t\t\t   +--------------------+" << endl;
					cout << "\t\t\t\t   |      密码错误      |" << endl;
					cout << "\t\t\t\t   +--------------------+" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (choice == "1")
		{
			int acc_state = accountSystem.stu_load_in();
			if (acc_state==1) {
				int flag = 1;
				while (flag) {
					string choice;
					string choice1;
					system("cls");
					cout << "\n\n\t\t\t*******************欢迎来到学生信息管理系统********************" << endl;
					cout << "\t\t\t你可以进行以下操作:" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              1   查询个人信息                               |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              2   修改登录密码                               |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              3   返回初始页面                               |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              0   退出系统                                   |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t请选择【0-3】：";
					cin >> choice;
					while (choice != "1" && choice != "2" && choice != "3" && choice != "0")
					{
						cout << "\t\t\t输入不合法,请重新选择【1-2】：";
						cin >> choice;
					}
					if (choice == "1")
					{
						underSystem.under_display_one(now);
					}
					else if (choice == "2")
					{
						accountSystem.change_pass(now);
						continue;
					}
					else if (choice == "3") {
						flag = 0;
					}
					else if (choice == "0") {
						exit(0);
					}
				}
			}
			else if (acc_state == 2) {
				int flag = 1;
				while (flag) {
					string choice;
					string choice1;
					system("cls");
					cout << "\n\n\t\t\t*******************欢迎来到学生信息管理系统********************" << endl;
					cout << "\t\t\t你可以进行以下操作:" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              1   查询个人信息                               |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              2   修改登录密码                               |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              3   返回初始页面                               |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t|              0   退出系统                                   |" << endl;
					cout << "\t\t\t|-------------------------------------------------------------|" << endl;
					cout << "\t\t\t请选择【0-3】：";
					cin >> choice;
					while (choice != "1" && choice != "2" && choice != "3" && choice != "0")
					{
						cout << "\t\t\t输入不合法,请重新选择【1-2】：";
						cin >> choice;
					}
					if (choice == "1")
					{
						postSystem.post_display_one(now);
					}
					else if (choice == "2")
					{
						accountSystem.change_pass(now);
						continue;
					}
					else if (choice == "3") {
						flag = 0;
					}
					else if (choice == "0") {
						exit(0);
					}
				}
			}
			else {
				continue;
			}
		}
		else if (choice == "0")
			exit(0);
	}

	return 0;
}