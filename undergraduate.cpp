#include "undergraduate.h"
#include<iostream>
#include <fstream>
#include<iomanip>
#include<string>
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
using std::sort;

stu_acc_manage accountSystem;

//展示某一本科生基本信息
void under_manager::under_base_display(undergraduate under)
{
	cout << "\t\t-----------------------------------------------------------------------" << endl;
	cout << "\t\t     学号:" << under.id << endl;
	cout << "\t\t     姓名:" << under.name << endl;
	cout << "\t\t     性别:" << under.gender << endl;
	cout << "\t\t 出生日期：" << under.data_of_birth.get_year() << "-" << under.data_of_birth.get_month() << "-"<< under.data_of_birth.get_day() << endl;
	cout << "\t\t     专业:" << under.major << endl;
	cout << "\t\t 手机号码:" << under.phone_num << endl;;
	cout << "\t\t 电子邮箱:" << under.email << endl;
	cout << "\t\t     班级:" << under.classNo<< endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
}

//展示某一本科生成绩信息
void under_manager::under_score_display(undergraduate under)
{
	cout << "\t\t-----------------------------------------------------------------------" << endl;

	for (int i = 0; i < under.sub_num; i++)
	{
		cout << "\t\t";
		cout << left << setw(45) << under.stu_score[i].get_subject()
		 << left << setw(6) << under.stu_score[i].get_score() << endl;
	}
	if (under.sub_num == 0) cout << "\t\t\t暂无成绩"<<endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
}

//本科生信息初始化
void under_manager::under_init()
{
	ifstream in_subFile("subject_info.txt");
	if (!in_subFile) {
		cout << "Failed to open subject_info.txt" << endl;
		return;
	}
	all_subject temp;
	for (int i = 0; i < 35; i++) {
		in_subFile >> temp.number >> temp.sub_name;
		All_sub.push_back(temp);
	}
	in_subFile.close();
	
	// 读取本科生信息
	ifstream in_underFile("undergraduate_information.txt");
	if (!in_underFile) {
		cout << "Failed to open undergraduate_information.txt" << endl;
		return;
	}

	int underCount;
	if (!(in_underFile >> underCount)) {
		underCount = 0; // 文件为空或读取失败时将 n 设置为 0
	}
	in_underFile.ignore(); // 跳过换行符

	for (int i = 0; i < underCount; ++i) {
		string id, name,gender, year, month, day, major, phone_num, email, classNo;
		int sub_num;
		double ave_score=0;

		in_underFile >> id >> name >> gender >> year >> month >> day >> major >> phone_num >> email >> classNo >> sub_num >> ave_score;

		// 读取各科成绩
		vector<subject_score> temp_ave_scores;
		for (int j = 0; j < sub_num; ++j) {
			string subject;
			double ave_score;
			in_underFile >> subject >> ave_score;
			temp_ave_scores.emplace_back(subject, ave_score);  //在容器末尾直接构造对象
		}

		underList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, classNo, temp_ave_scores, sub_num, ave_score);
		cout << "1" << endl;
	}
	in_underFile.close();
}

//本科生信息管理主菜单
void under_manager::under_menu()
{
	string choice = "0";
	system("cls");
	cout << "\n\n\t\t\t*******************欢迎来到本科生信息管理系统********************" << endl;
	cout << "\t\t\t你可以进行以下操作:" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        1   添加本科生信息      |     2   删除本科生信息         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        3   修改本科生信息      |     4   查询本科生信息         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        5   清空系统数据        |     6   统计本科生数据(排序)   |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        7   展示本科生信息      |     0   返回学生管理系统       |" << endl;
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
		this->under_create();
		this->under_menu();
	}
	else if (choice == "2")
	{
		this->under_delete();
		this->under_menu();
	}
	else if (choice == "3")
	{
		this->under_update();
		this->under_menu();
	}
	else if (choice == "4")
	{
		this->under_find();
		this->under_menu();
	}
	else if (choice == "5")
	{
		this->under_clear();
		this->under_menu();
	}
	else if (choice == "6")
	{
		this->under_sort();
		this->under_menu();
	}
	else if (choice == "7")
	{
		this->under_display();
		this->under_menu();
	}
	else if (choice == "0")
	{
		return;
	}
}

//将本科生信息写入到文件中
void under_manager::under_writefile()
{
	ofstream outfile;
	outfile.open("undergraduate_information.txt", ios::out);
	if (!outfile) {
		cerr << "Error opening file : undergraduate_information.txt" << endl;
		return;
	}

	outfile << underList.size() << endl;


	for (int i = 0; i < underList.size(); i++)
	{
		outfile << underList[i].id << " " << underList[i].name << " " <<underList[i].gender<< " "
			<< underList[i].data_of_birth.get_year() << " " << underList[i].data_of_birth.get_month() << " " 
			<< underList[i].data_of_birth.get_day() << " "<< underList[i].major << " " << underList[i].phone_num
			<< " " << underList[i].email << " "<< underList[i].classNo << " "  << underList[i].sub_num << " "
			<< underList[i].ave_score << " " <<endl;

		for (int j = 0; j < underList[i].sub_num; j++)//写入学生各科目成绩
		{
			outfile << underList[i].stu_score[j].get_subject() << " "
				<< underList[i].stu_score[j].get_score() << " ";
			if (j > 0 && j == underList[i].sub_num - 1)
			{
				outfile << endl;  //输入最后一科成绩时，向文件中写入回车
			}
		}
	}
	outfile.close();
}

//本科生信息添加功能
void under_manager::under_create()
{
	
	while (true) {
		system("cls");
		cout << "\t\t**********************欢迎来到本科生信息添加功能*************************" << endl;
		cout << "\t\t学生信息速览：" << endl;
		this->under_stuChart();
		cout << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t1 添加本科生信息" << endl;
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
			system("cls");
			under_example();
			string flag = "1";
			while (flag == "1")
			{
				string id, name,gender, year, month, day, major, phone_num, email, classNo;
				vector<subject_score> stu_scores;
				int sub_num=0 ;
				double ave_score=0.0 ;
				cout << "\t\t输入本科生信息：" << endl;
				cout << "\t\t请输入学号：";
				bool check = false;
				do
				{
					check = false;
					cin >> id;
					for (int i = 0; i < underList.size(); ++i)
					{
						if (id == underList[i].id)
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
				cout << "\t\t请输入班级：";
				cin >> classNo;
				


				string option = "1";
				cout << "\t\t是否添加成绩信息？（1 是 0 否）" << endl;
				cout << "\t\t请进行选择【0-1】：";
				cin >> option;
				while (option != "0" && option != "1")
				{
					cout << "\t\t输入不合法,请重新选择【0-1】：";
					cin >> option;
				}
				if (option == "1")
				{
					int temp;
					int cnt = 0;
					while (option == "1")
					{	
						system("cls");
						/*所有科目展示*/
						cout << "\n\n\t\t\t**************************可录入课程名称及代号******************************" << endl;
						cout << "\t\t\t+--------------------------------------------------------------------------------+" << endl;
						cout << "\t\t\t|  1 高等数学    | 8 解析几何    | 15 近世代数   | 22  物理化学  | 29 形势与政策 |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  2 线性代数    | 9 高等代数    | 16 计算机网络 | 23  微观化学  | 30 系统工程学 |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  3 概率统计    | 10 马克思主义 | 17 计算机组成 | 24  军事理论  | 31 信息统计学 |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  4 离散数学    | 11 习近平思想 | 18 解剖学     | 25  大学英语  | 32 数据库原理 |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  5 数据结构    | 12 道德与法治 | 19 麻醉学     | 26  学术英语  | 33 运筹学     |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  6 操作系统    | 13 数学建模   | 20 高等化学   | 27  雅思听说  | 34 宏观经济学 |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  7 大学物理    | 14 C语言设计  | 21 结构化学   | 28  托福读写  | 35 体育       |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|                                  其他课程未添加                                |" << endl;
						cout << "\t\t\t+--------------------------------------------------------------------------------+" << endl;
						cout << "\t\t\t请参考上述课程代号选择您所要添加的课程名称：" << endl;
						
						cnt++;
						string subject;
						double score=0.0;
						cout << "\t\t\t第" << cnt << "科科目编号：";
						while (true) {
							cin >> temp;
							if (temp < 1 || temp>35) {
								cout << "\t\t\t输入不合法,请重新输入：";
							}
							else break;
						}
						subject = All_sub[temp-1].sub_name;

						cout << "\t\t\t第" << cnt << "科科目成绩：";
						cin >> score;
						stu_scores.emplace_back(subject, score);
						ave_score += score;
						cout << "\t\t\t该科成绩信息添加成功！是否继续添加？（1 是 0 否）" << endl;
						cout << "\t\t\t请进行选择【0-1】：";
						cin >> option;
						while (option != "0" && option != "1")
						{
							cout << "\t\t\t输入不合法,请重新选择【0-1】：";
							cin >> option;
						}
					}
					sub_num = cnt;
				}
					
				
				if (sub_num)  ave_score /= sub_num; //计算平均分
				underList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, classNo, stu_scores, sub_num, ave_score);


				under_id = id;
				accountSystem.stu_acc_in2();
				under_writefile();
				cout << "\n\t\t该本科生信息添加成功！是否继续添加？（1 是 0 否）" << endl;
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

//本科生信息删除功能
void under_manager::under_delete()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************欢迎来到学生信息删除功能***********************" << endl;
		string choice;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 按学号删除" << endl;
		cout << "\t\t2 按姓名删除" << endl;
		cout << "\t\t0 返回主菜单" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t请进行选择【0-2】：";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新选择【0-2】：";
			cin >> choice;
		}
		if (choice == "1")
		{
			string keyID;
			bool flag = false;
			cout << "\t\t请输入待删除学生的学号：";
			cin >> keyID;
			for (vector<undergraduate>::iterator it = underList.begin(); it != underList.end(); ++it)
			{
				if (it->id == keyID)
				{
					flag = true;

					cout << "\t\t待删除学生的信息如下：" << endl;
					cout << "\t\t-----------------------------------------------------------------------" << endl;
					cout << "\t\t基本信息：" << endl;
					under_base_display(*it);
					cout << "\t\t成绩信息：" << endl;
					under_score_display(*it);

					cout << "\t\t确认删除？（1 是 0 否）" << endl;
					cout << "\t\t请进行选择【0-1】：";
					string ch = "0";
					cin >> ch;
					while (ch != "0" && ch != "1")
					{
						cout << "\t\t输入不合法,请重新选择【0-1】：";
						cin >> ch;
					}
					if (ch == "0") break;
					else
					{
						old_under_id = it->id;
						underList.erase(it);
						under_writefile();
						accountSystem.stu_delete();
						cout << "\t\t删除成功！" << endl;
						break;
					}
				}
			}
			if (!flag) cout << "\t\t查无此人，无法删除！\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "2")
		{
			string keyName;
			bool flag = false;
			cout << "\t\t请输入待删除学生的姓名：";
			cin >> keyName;
			for (vector<undergraduate>::iterator it = underList.begin(); it != underList.end(); ++it)
			{
				if (it->name == keyName)
				{
					flag = true;

					cout << "\t\t待删除学生的信息如下：" << endl;
					cout << "\t\t基本信息：" << endl;
					under_base_display(*it);
					cout << "\t\t成绩信息：" << endl;
					under_score_display(*it);

					cout << "\t\t确认删除？（1 是 0 否）" << endl;
					cout << "\t\t请进行选择【0-1】：";
					string ch = "0";
					cin >> ch;
					while (ch != "0" && ch != "1")
					{
						cout << "\t\t输入不合法,请重新选择【0-1】：";
						cin >> ch;
					}
					if (ch == "0") break;
					else
					{
						old_under_id = it->id;
						underList.erase(it);
						under_writefile();
						accountSystem.stu_delete();
						cout << "\t\t删除成功！" << endl;
						break;
					}
				}
			}
			if (!flag) cout << "\t\t查无此人，无法删除！\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "0")
		{
			break;
		}
	}
}

//本科生信息修改功能
void under_manager::under_update()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************欢迎来到修改学生信息功能***********************" << endl;
		string choice;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 修改本科生基本信息" << endl;
		cout << "\t\t2 修改本科生成绩信息" << endl;
		cout << "\t\t0 返回主菜单" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t请进行选择【0-2】：";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新选择【0-2】：";
			cin >> choice;
		}

		if (choice == "1")
		{
			bool flag = false;
			string keyID;
			cout << "\t\t请输入待修改学生的学号：";
			cin >> keyID;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].id == keyID)
				{
					flag = true;
					cout << "\t\t待修改本科生基本信息如下：" << endl;

					under_base_display(underList[i]);

					string select;
					cout << "\t\t接下来请输入您要修改的学生信息：" << endl;
					cout << "\t\t1.学号 2.姓名 3.性别 4.出生日期 5.专业 6.手机号码 7.电子邮箱 8.班级" << endl;
					cout << "\t\t请输入【1-8】：";
					cin >> select;
					while (select != "1" && select != "2" && select != "3" && select != "4" && select != "5" && select != "6" && select != "7" && select != "8")
					{
						cout << "\t\t\t输入不合法,请重新选择【0-7】：";
						cin >> select;
					}
					if (select == "1")
					{
						string id;
						cout << "\t\t请输入修改后的学号：";
						bool check = false;
						do
						{
							check = false;
							cin >> id;
							for (int j = 0; j < underList.size(); ++j)
							{
								if (id == underList[j].id && i != j)
								{
									cout << "\t\t该学号已被录入，请重新输入学号：";
									check = true;
								}
							}
						} while (check);
						old_under_id = underList[i].id;
						underList[i].id = id;
						under_writefile();
						under_id = id;
						accountSystem.acc_update();
						cout << "\t\t修改成功！" << endl;
						system("pause");
						continue;
					}
					else if (select == "2")
					{
						string name;
						cout << "\t\t请输入修改后的姓名：";
						cin >> name;
						underList[i].name = name;
						under_writefile();
						cout << "\t\t修改成功！" << endl;
						system("pause");
						continue;
					}
					else if (select == "3")
					{
						string gender;
						cout << "\t\t请输入修改后的性别：";
						cin >> gender;
						underList[i].gender = gender;
						under_writefile();
						cout << "\t\t修改成功！" << endl;
						system("pause");
						continue;
					}
					else if (select == "4")
					{
						string year, month, day;
						cout << "\t\t请输入修改后出生年份：";
						cin >> year;
						cout << "\t\t请输入修改后出生月份：";
						cin >> month;
						cout << "\t\t请输入修改后出生日：";
						cin >> day;
						underList[i].change_birth(year, month, day);
						under_writefile();
						cout << "\t\t修改成功！" << endl;
						system("pause");
						continue;
					}
					else if (select == "5")
					{
						string major;
						cout << "\t\t请输入修改后的专业：";
						cin >> major;
						underList[i].major = major;
						under_writefile();
						cout << "\t\t修改成功！" << endl;
						system("pause");
						continue;
					}
					else if (select == "6")
					{
						string phone_num;
						cout << "\t\t请输入修改后的电话号码：";
						cin >> phone_num;
						underList[i].phone_num = phone_num;
						under_writefile();
						cout << "\t\t修改成功！" << endl;
						system("pause");
						continue;
					}
					else if (select == "7")
					{
						string email;
						cout << "\t\t请输入修改后的电子邮箱：";
						cin >> email;
						underList[i].email = email;
						cout << "\t\t修改成功！" << endl;
						under_writefile();
						system("pause");
						continue;
					}
					else if (select == "8")
					{
						string classNo;
						cout << "\t\t请输入修改后的班级：";
						cin >> classNo;
						underList[i].classNo = classNo;
						cout << "\t\t修改成功！" << endl;
						under_writefile();
						system("pause");
						continue;
					}
				}
			}
			if (!flag)
			{
				cout << "\t\t查无此人，无法修改！\n" << endl;
				system("pause");
				continue;
			}
		}
		else if (choice == "2")
		{
			bool flag1 = false;
			string keyID;
			cout << "\t\t请输入待修改学生的学号：";
			cin >> keyID;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].id == keyID)
				{
					flag1 = true;
					cout << "\t\t待修改本科生成绩信息如下：" << endl;
					under_score_display(underList[i]);

					string sub;
					bool flag2 = false;
					cout << "\t\t请输入要修改的科目名称：";
					cin >> sub;
					for (int j = 0; j < underList[i].sub_num; j++)
					{
						if (underList[i].stu_score[j].get_subject() == sub)
						{
							flag2 = true;
							string change_sub;
							double change_score;
							cout << "\t\t请输入修改后的科目名称：";
							cin >> change_sub;
							cout << "\t\t请输入要修改后科目成绩：";
							cin >> change_score;
							underList[i].stu_score[j].change_subject(change_sub);
							underList[i].stu_score[j].change_score(change_score);
							//计算平均分
							underList[i].ave_score = 0;
							for (int k = 0; k < underList[i].sub_num; k++)
							{
								underList[i].ave_score += underList[i].stu_score[k].get_score();
							}
							underList[i].ave_score /= underList[i].sub_num;
							under_writefile();
							cout << "\t\t修改成功！" << endl;
							system("pause");
							continue;
						}
					}
					if (!flag2)
					{
						cout << "\t\t该学生没有录入该科目成绩信息！" << endl;
						system("pause");
						continue;
					}
				}
			}
			if (!flag1)
			{
				cout << "\t\t查无此人，无法修改！\n" << endl;
				system("pause");
				continue;
			}
		}
		else if (choice == "0")
		{
			break;
		}
	}
}

//本科生信息查询功能
void under_manager::under_find()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************欢迎来到本科生信息查询功能************************" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 按学号查询" << endl;
		cout << "\t\t2 按姓名查询" << endl;
		cout << "\t\t0 返回主菜单" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t请进行选择【0-2】：";
		string choice = "0";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新选择【0-2】：";
			cin >> choice;
		}
		if (choice == "1")
		{
			string keyID;
			bool flag = false;
			cout << "\t\t请输入待查询学生的学号：";
			cin >> keyID;
			cout << "\t\t查询结果如下：" << endl;
			cout << "\t\t学生信息：" << endl;
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].id == keyID)
				{
					flag = true;
					cout << "\t\t该本科生基本信息如下：" << endl;
					under_base_display(underList[i]);
					cout << "\t\t该本科生成绩信息如下：" << endl;
					under_score_display(underList[i]);
					break;
				}
			}
			if (!flag) cout << "\t\t查无此人！\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "2")
		{
			string keyName;
			bool flag = false;
			cout << "\t\t请输入待查询联系人的姓名：";
			cin >> keyName;
			cout << "\t\t查询结果如下：" << endl;
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].name == keyName)
				{
					flag = true;
					cout << "\t\t该本科生基本信息如下：" << endl;
					under_base_display(underList[i]);
					cout << "\t\t该本科生成绩信息如下：" << endl;
					under_score_display(underList[i]);
				}
			}
			if (!flag) cout << "\t\t查无此人！\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if(choice== "0")
		{
			break;
		}
	}
}

//本科生信息清空功能
void under_manager::under_clear()
{
	while (true)
	{
		string choice = "0";
		system("cls");
		cout << "\t\t**************欢迎来到清空系统数据功能***************" << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t1 确认清空系统数据" << endl;
		cout << "\t\t0 返回主菜单" << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t请慎重选择【0-1】：";
		cin >> choice;
		while (choice != "1" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新输入【1-2】：";
			cin >> choice;
		}
		if (choice == "1")
		{
			cout << "\t\t您确认要删除所有本科生数据吗？（1 是 0 否）" << endl;
			cout << "\t\t请进行选择【0-1】：";
			string ch = "0";
			cin >> ch;
			while (ch != "0" && ch != "1")
			{
				cout << "\t\t输入不合法,请重新选择【0-1】：";
				cin >> ch;
			}
			if (ch == "0") {
				break;
			}
			else if (ch == "1")
			{
				underList.clear();
				under_writefile();
				accountSystem.stu_clear();
				cout << "\t\t所有本科生信息已成功清空！" << endl;
				cout << "\t\t";
				system("pause");
			}
		}
		else if (choice == "0")
		{
			break;
		}
	}
}

// //为vector里面sort函数提供比较函数，按学号排序
bool cmp_ID( undergraduate& s1, undergraduate& s2)
{
	return s1.get_id() < s2.get_id();
}

//为vector里面sort函数提供比较函数，按平均分排序
bool cmp_score(undergraduate& s1, undergraduate& s2)
{
	if (s1.get_id() != s2.get_id()) return s1.get_ave() > s2.get_ave();
	else return s1.get_id() < s2.get_id();
}

//本科生信息统计（排序）功能,上面两个函数为下面的统计服务
void under_manager::under_sort()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************欢迎来到统计学生数据功能************************" << endl;
		string choice;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 按学号排序" << endl;
		cout << "\t\t2 按平均分排序" << endl;
		cout << "\t\t0 返回主菜单" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t请进行选择【0-2】：";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新选择【1-3】：";
			cin >> choice;
		}
		if (choice == "1")
		{
			sort(underList.begin(), underList.end(), cmp_ID);
			cout << "\t\t按学号升序排列如下：" << endl;
			under_stuChart();
			cout << "\t\t一共 " << underList.size() << " 人。" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "2")
		{
			sort(underList.begin(), underList.end(), cmp_score);
			cout << "\t\t按平均分降序排列如下：" << endl;
			under_stuChart();

			int z[10] = { 0 };
			double ave_score[5] = { 0,0,0,0,0 };
			double totalave_score = 0;
			for (int i = 0; i < underList.size(); ++i)
			{
				totalave_score += underList[i].ave_score;
				if (0 <= underList[i].ave_score && underList[i].ave_score < 60)
				{
					z[0]++; ave_score[0] += underList[i].ave_score;
				}	
				else if (60 <= underList[i].ave_score && underList[i].ave_score < 70)
				{
					z[1]++; ave_score[1] += underList[i].ave_score;
				}
				else if (70 <= underList[i].ave_score && underList[i].ave_score < 80)
				{
					z[2]++; ave_score[2] += underList[i].ave_score;

				}
				else if (80 <= underList[i].ave_score && underList[i].ave_score < 90)
				{
					z[3]++;
					ave_score[3] += underList[i].ave_score;
				}
				else { z[4]++; ave_score[4] += underList[i].ave_score; }
			}
			for (int i = 0; i <= 4; i++) {
				
				if(z[i]) ave_score[i] /= z[i];
				
			}
			cout << "\t\t-----------------------------------------------";
			cout << "\n\t\t";
			cout << left << setw(18) << "成绩等级";
			cout << left << setw(10) << "人数";
			cout << left << setw(10) << "平均分";
			cout << "\n\t\t-----------------------------------------------";
			cout << endl;
			cout << "\t\t不及格            " << z[0] << "         " << ave_score[0] << endl;
			cout << "\t\t及格              " << z[1] << "         " << ave_score[1] << endl;
			cout << "\t\t中等              " << z[2] << "         " << ave_score[2] << endl;
			cout << "\t\t良好              " << z[3] << "         " << ave_score[3] << endl;
			cout << "\t\t优秀              " << z[4] << "         " << ave_score[4] << endl;
			cout << "\t\t总计              " << underList.size() << "         " << totalave_score / underList.size() << endl;
			cout << "\t\t-----------------------------------------------" << endl;
			system("pause");
		}
		else if(choice=="0")
		{
			break;
		}
	}
}

//展示一位同学的信息
void under_manager::under_display_one(int i)
{
	system("cls");
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << "学号";
	cout << left << setw(10) << "姓名";
	cout << left << setw(5) << "性别";
	cout << left << setw(20) << "专业";
	cout << left << setw(15) << "班级";
	cout << left << setw(8) << "平均分";
	cout << left << setw(15) << "电话号码";
	cout << left << setw(22) << "电子邮箱";
	cout << left << setw(15) << "出生日期";
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << underList[i].get_id();
	cout << left << setw(10) << underList[i].name;
	cout << left << setw(5) << underList[i].gender;
	cout << left << setw(20) << underList[i].major;
	cout << left << setw(15) << underList[i].classNo;
	cout << left << setw(8) << underList[i].ave_score;
	cout << left << setw(15) << underList[i].phone_num;
	cout << left << setw(22) << underList[i].email;
	cout << left << underList[i].data_of_birth.get_year() << "-" << underList[i].data_of_birth.get_month() << "-" << underList[i].data_of_birth.get_day();
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
	cout << "\t\t";
	cout << left << setw(15) << "学号";
	cout << left << setw(10) << "姓名";
	cout << left << setw(36) << "科目";
	cout << left << setw(6) << "分数" << endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
	cout << "\t\t";
	cout << left << setw(15) << underList[i].id;
	cout << left << setw(10) << underList[i].name;
	for (int j = 0; j < underList[i].sub_num; j++)
	{

		if (j >= 1) { cout << "\t\t   "; cout << setw(22) << " "; }
		cout << left << setw(36) << underList[i].stu_score[j].get_subject();
		cout << left << setw(6) << underList[i].stu_score[j].get_score() << endl;
	}
	if (underList[i].sub_num == 0) cout << "\t     暂无成绩" << endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
	system("pause");

}
//本科生信息展示功能
void under_manager::under_display()
{
	while (true) {

		system("cls");
		cout << "\t\t***********************欢迎来到显示信息列表功能************************" << endl;
		cout << "\t\t请选择你想展示的信息:" << endl;
		cout << "\t\t\t1.本科生基本信息" << endl;
		cout << "\t\t\t2.本科生成绩信息" << endl;
		cout << "\t\t\t0.返回主菜单" << endl;
		cout << "\t\t请输入【0-2】：";
		string choice;
		int none_score = 0;
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t输入不合法,请重新输入【0-2】：";
			cin >> choice;
		}
		if (choice == "1") {
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << left << setw(15) << "学号";
			cout << left << setw(10) << "姓名";
			cout << left << setw(5) << "性别";
			cout << left << setw(20) << "专业";
			cout << left << setw(15) << "班级";
			cout << left << setw(8) << "平均分";
			cout << left << setw(15) << "电话号码";
			cout << left << setw(22) << "电子邮箱";
			cout << left << setw(15) << "出生日期";
			cout << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < underList.size(); i++)
			{
				cout << left << setw(15) << underList[i].get_id();
				cout << left << setw(10) << underList[i].name;
				cout << left << setw(5) << underList[i].gender;
				cout << left << setw(20) << underList[i].major;
				cout << left << setw(15) << underList[i].classNo;
				cout << left << setw(8) << underList[i].ave_score;
				cout << left << setw(15) << underList[i].phone_num;
				cout << left << setw(22) << underList[i].email;
				cout << left << underList[i].data_of_birth.get_year() << "-" << underList[i].data_of_birth.get_month() << "-" << underList[i].data_of_birth.get_day();
				cout << endl;
			}
			if (underList.size() == 0) cout << "\t\t\t\t\t\t当前暂无学生"<<endl;
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			system("pause");

		}
		else if (choice == "2") {
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			cout << "\t\t";
			cout << left << setw(15) << "学号";
			cout << left << setw(10) << "姓名";
			cout << left << setw(36) << "科目";
			cout << left << setw(6) << "分数" << endl;
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			for (int i = 0; i < underList.size(); i++)
			{
				cout << "\t\t";
				cout << left << setw(15) << underList[i].id;
				cout << left << setw(10) << underList[i].name;

				for (int j = 0; j < underList[i].sub_num; j++)
				{

					if (j >= 1) { cout << "\t\t   "; cout << setw(22) << " "; }
					cout << left << setw(36) << underList[i].stu_score[j].get_subject();
					cout << left << setw(6) << underList[i].stu_score[j].get_score() << endl;


				}
				if (underList[i].sub_num == 0) cout << "\t     暂无成绩" << endl;
				cout << "\t\t-----------------------------------------------------------------------" << endl;
			}


			system("pause");
		}
		else if (choice == "0") {
			break;
		}
	}
}
//本科生基本信息一览表
void under_manager::under_example()
{
	cout << "\t\t示例：" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t学号\t姓名\t性别\t出生日期\t专业\t电话\t\t\t邮箱\t\t班级" << endl;
	cout << "\t\t2023001\t张三\t男\t2001-01-01\t计算机\t12345678901\tzhangsan@example.com\tCS01" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t学科数\t平均分\t科目一名称\t科目一成绩\t科目二名称\t科目二成绩" << endl;
	cout << "\t\t2\t98\t高数\t\t100\t\t英语\t\t96" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;

}

//学生信息速览
void under_manager::under_stuChart() {
	
	cout << "\t\t---------------------------------------------------------------------------------" << endl;
	cout << "\t\t";
		cout << left << setw(15) << "学号";
		cout << left << setw(10) << "姓名";
		cout << left << setw(5) << "性别";
		cout << left << setw(20) << "专业";
		cout << left << setw(20) << "班级";
		cout << left << setw(6) << "平均分" << endl;
		cout << "\t\t---------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < underList.size(); i++) {
		cout << "\t\t";
		cout << left << setw(15) << underList[i].get_id();
		cout << left << setw(10) << underList[i].name;
		cout << left << setw(5) << underList[i].gender;
		cout << left << setw(20) << underList[i].major;
		cout << left << setw(20) << underList[i].classNo;
		cout << left << setw(6) << underList[i].ave_score<<endl;
	}
	if (underList.empty()) cout << "\t\t\t\t\t\t当前暂无学生哦~\n";
	cout << "\t\t---------------------------------------------------------------------------------" << endl;
}