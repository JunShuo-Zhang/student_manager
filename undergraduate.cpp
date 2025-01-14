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

//չʾĳһ������������Ϣ
void under_manager::under_base_display(undergraduate under)
{
	cout << "\t\t-----------------------------------------------------------------------" << endl;
	cout << "\t\t     ѧ��:" << under.id << endl;
	cout << "\t\t     ����:" << under.name << endl;
	cout << "\t\t     �Ա�:" << under.gender << endl;
	cout << "\t\t �������ڣ�" << under.data_of_birth.get_year() << "-" << under.data_of_birth.get_month() << "-"<< under.data_of_birth.get_day() << endl;
	cout << "\t\t     רҵ:" << under.major << endl;
	cout << "\t\t �ֻ�����:" << under.phone_num << endl;;
	cout << "\t\t ��������:" << under.email << endl;
	cout << "\t\t     �༶:" << under.classNo<< endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
}

//չʾĳһ�������ɼ���Ϣ
void under_manager::under_score_display(undergraduate under)
{
	cout << "\t\t-----------------------------------------------------------------------" << endl;

	for (int i = 0; i < under.sub_num; i++)
	{
		cout << "\t\t";
		cout << left << setw(45) << under.stu_score[i].get_subject()
		 << left << setw(6) << under.stu_score[i].get_score() << endl;
	}
	if (under.sub_num == 0) cout << "\t\t\t���޳ɼ�"<<endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
}

//��������Ϣ��ʼ��
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
	
	// ��ȡ��������Ϣ
	ifstream in_underFile("undergraduate_information.txt");
	if (!in_underFile) {
		cout << "Failed to open undergraduate_information.txt" << endl;
		return;
	}

	int underCount;
	if (!(in_underFile >> underCount)) {
		underCount = 0; // �ļ�Ϊ�ջ��ȡʧ��ʱ�� n ����Ϊ 0
	}
	in_underFile.ignore(); // �������з�

	for (int i = 0; i < underCount; ++i) {
		string id, name,gender, year, month, day, major, phone_num, email, classNo;
		int sub_num;
		double ave_score=0;

		in_underFile >> id >> name >> gender >> year >> month >> day >> major >> phone_num >> email >> classNo >> sub_num >> ave_score;

		// ��ȡ���Ƴɼ�
		vector<subject_score> temp_ave_scores;
		for (int j = 0; j < sub_num; ++j) {
			string subject;
			double ave_score;
			in_underFile >> subject >> ave_score;
			temp_ave_scores.emplace_back(subject, ave_score);  //������ĩβֱ�ӹ������
		}

		underList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, classNo, temp_ave_scores, sub_num, ave_score);
		cout << "1" << endl;
	}
	in_underFile.close();
}

//��������Ϣ�������˵�
void under_manager::under_menu()
{
	string choice = "0";
	system("cls");
	cout << "\n\n\t\t\t*******************��ӭ������������Ϣ����ϵͳ********************" << endl;
	cout << "\t\t\t����Խ������²���:" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        1   ��ӱ�������Ϣ      |     2   ɾ����������Ϣ         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        3   �޸ı�������Ϣ      |     4   ��ѯ��������Ϣ         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        5   ���ϵͳ����        |     6   ͳ�Ʊ���������(����)   |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        7   չʾ��������Ϣ      |     0   ����ѧ������ϵͳ       |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t��ѡ��0-7����";
	cin >> choice;
	while (choice != "0" && choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7")
	{
		cout << "\t\t\t���벻�Ϸ�,������ѡ��0-8����";
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

//����������Ϣд�뵽�ļ���
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

		for (int j = 0; j < underList[i].sub_num; j++)//д��ѧ������Ŀ�ɼ�
		{
			outfile << underList[i].stu_score[j].get_subject() << " "
				<< underList[i].stu_score[j].get_score() << " ";
			if (j > 0 && j == underList[i].sub_num - 1)
			{
				outfile << endl;  //�������һ�Ƴɼ�ʱ�����ļ���д��س�
			}
		}
	}
	outfile.close();
}

//��������Ϣ��ӹ���
void under_manager::under_create()
{
	
	while (true) {
		system("cls");
		cout << "\t\t**********************��ӭ������������Ϣ��ӹ���*************************" << endl;
		cout << "\t\tѧ����Ϣ������" << endl;
		this->under_stuChart();
		cout << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t1 ��ӱ�������Ϣ" << endl;
		cout << "\t\t0 �������˵�" << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t��ѡ��0-1����";
		string choice;
		cin >> choice;
		while (choice != "1" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,���������롾0-1����";
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
				cout << "\t\t���뱾������Ϣ��" << endl;
				cout << "\t\t������ѧ�ţ�";
				bool check = false;
				do
				{
					check = false;
					cin >> id;
					for (int i = 0; i < underList.size(); ++i)
					{
						if (id == underList[i].id)
						{
							cout << "\t\t��ѧ���Ѵ��ڣ����������룺";
							check = true;
						}
					}
				} while (check);
				cout << "\t\t������������";
				cin >> name;
				while (1) {
					cout << "\t\t�������Ա�";
					cin >> gender;
					if (gender != "��" && gender != "Ů")
						cout << "\t\t���벻�Ϸ�,���������룺";
					else break;

				}
				cout << "\t\t�����������ݣ�";
				cin >> year;
				cout << "\t\t����������·ݣ�";
				cin >> month;
				cout << "\t\t����������գ�";
				cin >> day;
				cout << "\t\t������רҵ��";
				cin >> major;
				cout << "\t\t������绰���룺";
				cin >> phone_num;
				cout << "\t\t������������䣺";
				cin >> email;
				cout << "\t\t������༶��";
				cin >> classNo;
				


				string option = "1";
				cout << "\t\t�Ƿ���ӳɼ���Ϣ����1 �� 0 ��" << endl;
				cout << "\t\t�����ѡ��0-1����";
				cin >> option;
				while (option != "0" && option != "1")
				{
					cout << "\t\t���벻�Ϸ�,������ѡ��0-1����";
					cin >> option;
				}
				if (option == "1")
				{
					int temp;
					int cnt = 0;
					while (option == "1")
					{	
						system("cls");
						/*���п�Ŀչʾ*/
						cout << "\n\n\t\t\t**************************��¼��γ����Ƽ�����******************************" << endl;
						cout << "\t\t\t+--------------------------------------------------------------------------------+" << endl;
						cout << "\t\t\t|  1 �ߵ���ѧ    | 8 ��������    | 15 ��������   | 22  ����ѧ  | 29 ���������� |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  2 ���Դ���    | 9 �ߵȴ���    | 16 ��������� | 23  ΢�ۻ�ѧ  | 30 ϵͳ����ѧ |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  3 ����ͳ��    | 10 ���˼���� | 17 �������� | 24  ��������  | 31 ��Ϣͳ��ѧ |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  4 ��ɢ��ѧ    | 11 ϰ��ƽ˼�� | 18 ����ѧ     | 25  ��ѧӢ��  | 32 ���ݿ�ԭ�� |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  5 ���ݽṹ    | 12 �����뷨�� | 19 ����ѧ     | 26  ѧ��Ӣ��  | 33 �˳�ѧ     |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  6 ����ϵͳ    | 13 ��ѧ��ģ   | 20 �ߵȻ�ѧ   | 27  ��˼��˵  | 34 ��۾���ѧ |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|  7 ��ѧ����    | 14 C�������  | 21 �ṹ��ѧ   | 28  �и���д  | 35 ����       |" << endl;
						cout << "\t\t\t|--------------------------------------------------------------------------------|" << endl;
						cout << "\t\t\t|                                  �����γ�δ���                                |" << endl;
						cout << "\t\t\t+--------------------------------------------------------------------------------+" << endl;
						cout << "\t\t\t��ο������γ̴���ѡ������Ҫ��ӵĿγ����ƣ�" << endl;
						
						cnt++;
						string subject;
						double score=0.0;
						cout << "\t\t\t��" << cnt << "�ƿ�Ŀ��ţ�";
						while (true) {
							cin >> temp;
							if (temp < 1 || temp>35) {
								cout << "\t\t\t���벻�Ϸ�,���������룺";
							}
							else break;
						}
						subject = All_sub[temp-1].sub_name;

						cout << "\t\t\t��" << cnt << "�ƿ�Ŀ�ɼ���";
						cin >> score;
						stu_scores.emplace_back(subject, score);
						ave_score += score;
						cout << "\t\t\t�ÿƳɼ���Ϣ��ӳɹ����Ƿ������ӣ���1 �� 0 ��" << endl;
						cout << "\t\t\t�����ѡ��0-1����";
						cin >> option;
						while (option != "0" && option != "1")
						{
							cout << "\t\t\t���벻�Ϸ�,������ѡ��0-1����";
							cin >> option;
						}
					}
					sub_num = cnt;
				}
					
				
				if (sub_num)  ave_score /= sub_num; //����ƽ����
				underList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, classNo, stu_scores, sub_num, ave_score);


				under_id = id;
				accountSystem.stu_acc_in2();
				under_writefile();
				cout << "\n\t\t�ñ�������Ϣ��ӳɹ����Ƿ������ӣ���1 �� 0 ��" << endl;
				cout << "\t\t�����ѡ��0-1����";
				cin >> flag;
				while (flag != "0" && flag != "1")
				{
					cout << "\t\t���벻�Ϸ�,������ѡ��0-1����";
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

//��������Ϣɾ������
void under_manager::under_delete()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************��ӭ����ѧ����Ϣɾ������***********************" << endl;
		string choice;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 ��ѧ��ɾ��" << endl;
		cout << "\t\t2 ������ɾ��" << endl;
		cout << "\t\t0 �������˵�" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t�����ѡ��0-2����";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,������ѡ��0-2����";
			cin >> choice;
		}
		if (choice == "1")
		{
			string keyID;
			bool flag = false;
			cout << "\t\t�������ɾ��ѧ����ѧ�ţ�";
			cin >> keyID;
			for (vector<undergraduate>::iterator it = underList.begin(); it != underList.end(); ++it)
			{
				if (it->id == keyID)
				{
					flag = true;

					cout << "\t\t��ɾ��ѧ������Ϣ���£�" << endl;
					cout << "\t\t-----------------------------------------------------------------------" << endl;
					cout << "\t\t������Ϣ��" << endl;
					under_base_display(*it);
					cout << "\t\t�ɼ���Ϣ��" << endl;
					under_score_display(*it);

					cout << "\t\tȷ��ɾ������1 �� 0 ��" << endl;
					cout << "\t\t�����ѡ��0-1����";
					string ch = "0";
					cin >> ch;
					while (ch != "0" && ch != "1")
					{
						cout << "\t\t���벻�Ϸ�,������ѡ��0-1����";
						cin >> ch;
					}
					if (ch == "0") break;
					else
					{
						old_under_id = it->id;
						underList.erase(it);
						under_writefile();
						accountSystem.stu_delete();
						cout << "\t\tɾ���ɹ���" << endl;
						break;
					}
				}
			}
			if (!flag) cout << "\t\t���޴��ˣ��޷�ɾ����\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "2")
		{
			string keyName;
			bool flag = false;
			cout << "\t\t�������ɾ��ѧ����������";
			cin >> keyName;
			for (vector<undergraduate>::iterator it = underList.begin(); it != underList.end(); ++it)
			{
				if (it->name == keyName)
				{
					flag = true;

					cout << "\t\t��ɾ��ѧ������Ϣ���£�" << endl;
					cout << "\t\t������Ϣ��" << endl;
					under_base_display(*it);
					cout << "\t\t�ɼ���Ϣ��" << endl;
					under_score_display(*it);

					cout << "\t\tȷ��ɾ������1 �� 0 ��" << endl;
					cout << "\t\t�����ѡ��0-1����";
					string ch = "0";
					cin >> ch;
					while (ch != "0" && ch != "1")
					{
						cout << "\t\t���벻�Ϸ�,������ѡ��0-1����";
						cin >> ch;
					}
					if (ch == "0") break;
					else
					{
						old_under_id = it->id;
						underList.erase(it);
						under_writefile();
						accountSystem.stu_delete();
						cout << "\t\tɾ���ɹ���" << endl;
						break;
					}
				}
			}
			if (!flag) cout << "\t\t���޴��ˣ��޷�ɾ����\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "0")
		{
			break;
		}
	}
}

//��������Ϣ�޸Ĺ���
void under_manager::under_update()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************��ӭ�����޸�ѧ����Ϣ����***********************" << endl;
		string choice;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 �޸ı�����������Ϣ" << endl;
		cout << "\t\t2 �޸ı������ɼ���Ϣ" << endl;
		cout << "\t\t0 �������˵�" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t�����ѡ��0-2����";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,������ѡ��0-2����";
			cin >> choice;
		}

		if (choice == "1")
		{
			bool flag = false;
			string keyID;
			cout << "\t\t��������޸�ѧ����ѧ�ţ�";
			cin >> keyID;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].id == keyID)
				{
					flag = true;
					cout << "\t\t���޸ı�����������Ϣ���£�" << endl;

					under_base_display(underList[i]);

					string select;
					cout << "\t\t��������������Ҫ�޸ĵ�ѧ����Ϣ��" << endl;
					cout << "\t\t1.ѧ�� 2.���� 3.�Ա� 4.�������� 5.רҵ 6.�ֻ����� 7.�������� 8.�༶" << endl;
					cout << "\t\t�����롾1-8����";
					cin >> select;
					while (select != "1" && select != "2" && select != "3" && select != "4" && select != "5" && select != "6" && select != "7" && select != "8")
					{
						cout << "\t\t\t���벻�Ϸ�,������ѡ��0-7����";
						cin >> select;
					}
					if (select == "1")
					{
						string id;
						cout << "\t\t�������޸ĺ��ѧ�ţ�";
						bool check = false;
						do
						{
							check = false;
							cin >> id;
							for (int j = 0; j < underList.size(); ++j)
							{
								if (id == underList[j].id && i != j)
								{
									cout << "\t\t��ѧ���ѱ�¼�룬����������ѧ�ţ�";
									check = true;
								}
							}
						} while (check);
						old_under_id = underList[i].id;
						underList[i].id = id;
						under_writefile();
						under_id = id;
						accountSystem.acc_update();
						cout << "\t\t�޸ĳɹ���" << endl;
						system("pause");
						continue;
					}
					else if (select == "2")
					{
						string name;
						cout << "\t\t�������޸ĺ��������";
						cin >> name;
						underList[i].name = name;
						under_writefile();
						cout << "\t\t�޸ĳɹ���" << endl;
						system("pause");
						continue;
					}
					else if (select == "3")
					{
						string gender;
						cout << "\t\t�������޸ĺ���Ա�";
						cin >> gender;
						underList[i].gender = gender;
						under_writefile();
						cout << "\t\t�޸ĳɹ���" << endl;
						system("pause");
						continue;
					}
					else if (select == "4")
					{
						string year, month, day;
						cout << "\t\t�������޸ĺ������ݣ�";
						cin >> year;
						cout << "\t\t�������޸ĺ�����·ݣ�";
						cin >> month;
						cout << "\t\t�������޸ĺ�����գ�";
						cin >> day;
						underList[i].change_birth(year, month, day);
						under_writefile();
						cout << "\t\t�޸ĳɹ���" << endl;
						system("pause");
						continue;
					}
					else if (select == "5")
					{
						string major;
						cout << "\t\t�������޸ĺ��רҵ��";
						cin >> major;
						underList[i].major = major;
						under_writefile();
						cout << "\t\t�޸ĳɹ���" << endl;
						system("pause");
						continue;
					}
					else if (select == "6")
					{
						string phone_num;
						cout << "\t\t�������޸ĺ�ĵ绰���룺";
						cin >> phone_num;
						underList[i].phone_num = phone_num;
						under_writefile();
						cout << "\t\t�޸ĳɹ���" << endl;
						system("pause");
						continue;
					}
					else if (select == "7")
					{
						string email;
						cout << "\t\t�������޸ĺ�ĵ������䣺";
						cin >> email;
						underList[i].email = email;
						cout << "\t\t�޸ĳɹ���" << endl;
						under_writefile();
						system("pause");
						continue;
					}
					else if (select == "8")
					{
						string classNo;
						cout << "\t\t�������޸ĺ�İ༶��";
						cin >> classNo;
						underList[i].classNo = classNo;
						cout << "\t\t�޸ĳɹ���" << endl;
						under_writefile();
						system("pause");
						continue;
					}
				}
			}
			if (!flag)
			{
				cout << "\t\t���޴��ˣ��޷��޸ģ�\n" << endl;
				system("pause");
				continue;
			}
		}
		else if (choice == "2")
		{
			bool flag1 = false;
			string keyID;
			cout << "\t\t��������޸�ѧ����ѧ�ţ�";
			cin >> keyID;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].id == keyID)
				{
					flag1 = true;
					cout << "\t\t���޸ı������ɼ���Ϣ���£�" << endl;
					under_score_display(underList[i]);

					string sub;
					bool flag2 = false;
					cout << "\t\t������Ҫ�޸ĵĿ�Ŀ���ƣ�";
					cin >> sub;
					for (int j = 0; j < underList[i].sub_num; j++)
					{
						if (underList[i].stu_score[j].get_subject() == sub)
						{
							flag2 = true;
							string change_sub;
							double change_score;
							cout << "\t\t�������޸ĺ�Ŀ�Ŀ���ƣ�";
							cin >> change_sub;
							cout << "\t\t������Ҫ�޸ĺ��Ŀ�ɼ���";
							cin >> change_score;
							underList[i].stu_score[j].change_subject(change_sub);
							underList[i].stu_score[j].change_score(change_score);
							//����ƽ����
							underList[i].ave_score = 0;
							for (int k = 0; k < underList[i].sub_num; k++)
							{
								underList[i].ave_score += underList[i].stu_score[k].get_score();
							}
							underList[i].ave_score /= underList[i].sub_num;
							under_writefile();
							cout << "\t\t�޸ĳɹ���" << endl;
							system("pause");
							continue;
						}
					}
					if (!flag2)
					{
						cout << "\t\t��ѧ��û��¼��ÿ�Ŀ�ɼ���Ϣ��" << endl;
						system("pause");
						continue;
					}
				}
			}
			if (!flag1)
			{
				cout << "\t\t���޴��ˣ��޷��޸ģ�\n" << endl;
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

//��������Ϣ��ѯ����
void under_manager::under_find()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************��ӭ������������Ϣ��ѯ����************************" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 ��ѧ�Ų�ѯ" << endl;
		cout << "\t\t2 ��������ѯ" << endl;
		cout << "\t\t0 �������˵�" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t�����ѡ��0-2����";
		string choice = "0";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,������ѡ��0-2����";
			cin >> choice;
		}
		if (choice == "1")
		{
			string keyID;
			bool flag = false;
			cout << "\t\t���������ѯѧ����ѧ�ţ�";
			cin >> keyID;
			cout << "\t\t��ѯ������£�" << endl;
			cout << "\t\tѧ����Ϣ��" << endl;
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].id == keyID)
				{
					flag = true;
					cout << "\t\t�ñ�����������Ϣ���£�" << endl;
					under_base_display(underList[i]);
					cout << "\t\t�ñ������ɼ���Ϣ���£�" << endl;
					under_score_display(underList[i]);
					break;
				}
			}
			if (!flag) cout << "\t\t���޴��ˣ�\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "2")
		{
			string keyName;
			bool flag = false;
			cout << "\t\t���������ѯ��ϵ�˵�������";
			cin >> keyName;
			cout << "\t\t��ѯ������£�" << endl;
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			for (int i = 0; i < underList.size(); i++)
			{
				if (underList[i].name == keyName)
				{
					flag = true;
					cout << "\t\t�ñ�����������Ϣ���£�" << endl;
					under_base_display(underList[i]);
					cout << "\t\t�ñ������ɼ���Ϣ���£�" << endl;
					under_score_display(underList[i]);
				}
			}
			if (!flag) cout << "\t\t���޴��ˣ�\n" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if(choice== "0")
		{
			break;
		}
	}
}

//��������Ϣ��չ���
void under_manager::under_clear()
{
	while (true)
	{
		string choice = "0";
		system("cls");
		cout << "\t\t**************��ӭ�������ϵͳ���ݹ���***************" << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t1 ȷ�����ϵͳ����" << endl;
		cout << "\t\t0 �������˵�" << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t������ѡ��0-1����";
		cin >> choice;
		while (choice != "1" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,���������롾1-2����";
			cin >> choice;
		}
		if (choice == "1")
		{
			cout << "\t\t��ȷ��Ҫɾ�����б����������𣿣�1 �� 0 ��" << endl;
			cout << "\t\t�����ѡ��0-1����";
			string ch = "0";
			cin >> ch;
			while (ch != "0" && ch != "1")
			{
				cout << "\t\t���벻�Ϸ�,������ѡ��0-1����";
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
				cout << "\t\t���б�������Ϣ�ѳɹ���գ�" << endl;
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

// //Ϊvector����sort�����ṩ�ȽϺ�������ѧ������
bool cmp_ID( undergraduate& s1, undergraduate& s2)
{
	return s1.get_id() < s2.get_id();
}

//Ϊvector����sort�����ṩ�ȽϺ�������ƽ��������
bool cmp_score(undergraduate& s1, undergraduate& s2)
{
	if (s1.get_id() != s2.get_id()) return s1.get_ave() > s2.get_ave();
	else return s1.get_id() < s2.get_id();
}

//��������Ϣͳ�ƣ����򣩹���,������������Ϊ�����ͳ�Ʒ���
void under_manager::under_sort()
{
	while (true)
	{
		system("cls");
		cout << "\t\t***********************��ӭ����ͳ��ѧ�����ݹ���************************" << endl;
		string choice;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t1 ��ѧ������" << endl;
		cout << "\t\t2 ��ƽ��������" << endl;
		cout << "\t\t0 �������˵�" << endl;
		cout << "\t\t-----------------" << endl;
		cout << "\t\t�����ѡ��0-2����";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,������ѡ��1-3����";
			cin >> choice;
		}
		if (choice == "1")
		{
			sort(underList.begin(), underList.end(), cmp_ID);
			cout << "\t\t��ѧ�������������£�" << endl;
			under_stuChart();
			cout << "\t\tһ�� " << underList.size() << " �ˡ�" << endl;
			cout << "\t\t";
			system("pause");
		}
		else if (choice == "2")
		{
			sort(underList.begin(), underList.end(), cmp_score);
			cout << "\t\t��ƽ���ֽ����������£�" << endl;
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
			cout << left << setw(18) << "�ɼ��ȼ�";
			cout << left << setw(10) << "����";
			cout << left << setw(10) << "ƽ����";
			cout << "\n\t\t-----------------------------------------------";
			cout << endl;
			cout << "\t\t������            " << z[0] << "         " << ave_score[0] << endl;
			cout << "\t\t����              " << z[1] << "         " << ave_score[1] << endl;
			cout << "\t\t�е�              " << z[2] << "         " << ave_score[2] << endl;
			cout << "\t\t����              " << z[3] << "         " << ave_score[3] << endl;
			cout << "\t\t����              " << z[4] << "         " << ave_score[4] << endl;
			cout << "\t\t�ܼ�              " << underList.size() << "         " << totalave_score / underList.size() << endl;
			cout << "\t\t-----------------------------------------------" << endl;
			system("pause");
		}
		else if(choice=="0")
		{
			break;
		}
	}
}

//չʾһλͬѧ����Ϣ
void under_manager::under_display_one(int i)
{
	system("cls");
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << "ѧ��";
	cout << left << setw(10) << "����";
	cout << left << setw(5) << "�Ա�";
	cout << left << setw(20) << "רҵ";
	cout << left << setw(15) << "�༶";
	cout << left << setw(8) << "ƽ����";
	cout << left << setw(15) << "�绰����";
	cout << left << setw(22) << "��������";
	cout << left << setw(15) << "��������";
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
	cout << left << setw(15) << "ѧ��";
	cout << left << setw(10) << "����";
	cout << left << setw(36) << "��Ŀ";
	cout << left << setw(6) << "����" << endl;
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
	if (underList[i].sub_num == 0) cout << "\t     ���޳ɼ�" << endl;
	cout << "\t\t-----------------------------------------------------------------------" << endl;
	system("pause");

}
//��������Ϣչʾ����
void under_manager::under_display()
{
	while (true) {

		system("cls");
		cout << "\t\t***********************��ӭ������ʾ��Ϣ�б���************************" << endl;
		cout << "\t\t��ѡ������չʾ����Ϣ:" << endl;
		cout << "\t\t\t1.������������Ϣ" << endl;
		cout << "\t\t\t2.�������ɼ���Ϣ" << endl;
		cout << "\t\t\t0.�������˵�" << endl;
		cout << "\t\t�����롾0-2����";
		string choice;
		int none_score = 0;
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "0")
		{
			cout << "\t\t���벻�Ϸ�,���������롾0-2����";
			cin >> choice;
		}
		if (choice == "1") {
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << left << setw(15) << "ѧ��";
			cout << left << setw(10) << "����";
			cout << left << setw(5) << "�Ա�";
			cout << left << setw(20) << "רҵ";
			cout << left << setw(15) << "�༶";
			cout << left << setw(8) << "ƽ����";
			cout << left << setw(15) << "�绰����";
			cout << left << setw(22) << "��������";
			cout << left << setw(15) << "��������";
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
			if (underList.size() == 0) cout << "\t\t\t\t\t\t��ǰ����ѧ��"<<endl;
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			system("pause");

		}
		else if (choice == "2") {
			cout << "\t\t-----------------------------------------------------------------------" << endl;
			cout << "\t\t";
			cout << left << setw(15) << "ѧ��";
			cout << left << setw(10) << "����";
			cout << left << setw(36) << "��Ŀ";
			cout << left << setw(6) << "����" << endl;
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
				if (underList[i].sub_num == 0) cout << "\t     ���޳ɼ�" << endl;
				cout << "\t\t-----------------------------------------------------------------------" << endl;
			}


			system("pause");
		}
		else if (choice == "0") {
			break;
		}
	}
}
//������������Ϣһ����
void under_manager::under_example()
{
	cout << "\t\tʾ����" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\tѧ��\t����\t�Ա�\t��������\tרҵ\t�绰\t\t\t����\t\t�༶" << endl;
	cout << "\t\t2023001\t����\t��\t2001-01-01\t�����\t12345678901\tzhangsan@example.com\tCS01" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\tѧ����\tƽ����\t��Ŀһ����\t��Ŀһ�ɼ�\t��Ŀ������\t��Ŀ���ɼ�" << endl;
	cout << "\t\t2\t98\t����\t\t100\t\tӢ��\t\t96" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------------------" << endl;

}

//ѧ����Ϣ����
void under_manager::under_stuChart() {
	
	cout << "\t\t---------------------------------------------------------------------------------" << endl;
	cout << "\t\t";
		cout << left << setw(15) << "ѧ��";
		cout << left << setw(10) << "����";
		cout << left << setw(5) << "�Ա�";
		cout << left << setw(20) << "רҵ";
		cout << left << setw(20) << "�༶";
		cout << left << setw(6) << "ƽ����" << endl;
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
	if (underList.empty()) cout << "\t\t\t\t\t\t��ǰ����ѧ��Ŷ~\n";
	cout << "\t\t---------------------------------------------------------------------------------" << endl;
}