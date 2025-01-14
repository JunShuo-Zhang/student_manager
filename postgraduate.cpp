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


//�о���������Ϣһ����
void post_manager::post_example()
{
	cout << "\t\tʾ����" << endl;
	cout << "\t--------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\tѧ��\t����\t�Ա�\t��������\tרҵ\t�绰\t\t����\t\t\t����\t\t��ʦ" << endl;
	cout << "\t2023001\t����\t��\t2000-12-12\t����\t98765432101\tlisi@example.com\t���Ӽ���\t������" << endl;
	cout << "\t--------------------------------------------------------------------------------------------------------------" << endl;
}

//�о�����Ϣ��ʼ��
void post_manager::post_init()
{
	// ��ȡ�о�����Ϣ
	ifstream in_postFile("postgraduate_information.txt");
	if (!in_postFile) {
		cout << "Failed to open postgraduate_information.txt" << endl;
		return;
	}

	int postCount;
	if (!(in_postFile >> postCount)) {
		postCount = 0; // �ļ�Ϊ�ջ��ȡʧ��ʱ�� n ����Ϊ 0
	}
	in_postFile.ignore(); // �������з�

	for (int i = 0; i < postCount; ++i) {
		string id, name,gender, year, month, day, major, phone_num, email, title, tutor;

		in_postFile >> id >> name >> gender >> year >> month >> day >> major >> phone_num >> email >> title >> tutor;

		postList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, title, tutor);
	}

	in_postFile.close();
}

//�о�����Ϣ�������˵�
void post_manager::post_menu()
{
	string choice = "0";
	system("cls");
	cout << "\n\n\t\t\t*******************��ӭ�����о�����Ϣ����ϵͳ********************" << endl;
	cout << "\t\t\t����Խ������²���:" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        1   ����о�����Ϣ      |     2   ɾ���о�����Ϣ         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        3   �޸��о�����Ϣ      |     4   ��ѯ�о�����Ϣ         |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        5   ����о�������      |     6   ͳ���о�������(����)   |" << endl;
	cout << "\t\t\t|-----------------------------------------------------------------|" << endl;
	cout << "\t\t\t|        7   չʾ�о�����Ϣ      |     0   ����ѧ������ϵͳ       |" << endl;
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

//���о�����Ϣд�뵽�ļ���
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

//�о�����Ϣ¼��
void post_manager::post_create()
{
	while (true) {
		system("cls");
		cout << "\t\t**********************��ӭ�����о�����Ϣ��ӹ���*************************" << endl;
		cout << "\t\t�о���������Ϣһ����" << endl;
		post_example();
		cout << endl;
		cout << "\t\t------------------" << endl;
		cout << "\t\t1 ����о�����Ϣ" << endl;
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
			string flag = "1";
			while (flag == "1")
			{
				string id, name,gender, year, month, day, major, phone_num, email, title, tutor;
				cout << "\t\t�����о�����Ϣ��" << endl;
				cout << "\t\t������ѧ�ţ�";
				bool check = false;
				do
				{
					check = false;
					cin >> id;
					for (int i = 0; i < postList.size(); ++i)
					{
						if (id == postList[i].id)
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
				cout << "\t\t�������о����⣺";
				cin >> title;
				cout << "\t\t�����뵼ʦ������";
				cin >> tutor;
				postList.emplace_back(id, name,gender, year, month, day, major, phone_num, email, title, tutor);
				post_writefile();
				post_id = id;
				accountSystem.stu_acc_in1();

				cout << "\n\t\t���о�����Ϣ��ӳɹ����Ƿ������ӣ���1 �� 0 ��" << endl;
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

//�о�����Ϣɾ������
void post_manager::post_delete()
{
	system("cls");
	cout << "\t\t**********************ɾ���о�����Ϣ*************************" << endl;
	cout << "\t\t������Ҫɾ�����о���ѧ�ţ�";
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
		cout << "\t\t�о�����Ϣɾ���ɹ���" << endl;
	}
	else {
		cout << "\t\tû���ҵ���ѧ�ŵ��о�����Ϣ��" << endl;
	}

	system("pause");
}

//�о�����Ϣ�޸Ĺ���
void post_manager::post_update()
{
	system("cls");
	cout << "\t\t**********************�޸��о�����Ϣ*************************" << endl;
	cout << "\t\t������Ҫ�޸���Ϣ���о���ѧ�ţ�";
	string id;
	cin >> id;

	auto it = std::find_if(postList.begin(), postList.end(), [&](postgraduate& p) {
		return p.id == id;
		});

	if (it != postList.end()) {	
		cout << "\t\t�ҵ��о�����Ϣ��" << endl;
		cout << "\t\tѧ�ţ�" << it->id << endl;
		cout << "\t\t������" << it->name << endl;
		cout << "\t\t�������ڣ�" << it->data_of_birth.get_year() << "-" << it->data_of_birth.get_month() << "-" << it->data_of_birth.get_day() << endl;
		cout << "\t\tרҵ��" << it->major << endl;
		cout << "\t\t�绰��" << it->phone_num << endl;
		cout << "\t\t���䣺" << it->email << endl;
		cout << "\t\t���⣺" << it->title << endl;
		cout << "\t\t��ʦ��" << it->tutor << endl;

		while (true)
		{
			cout << "\t\t��ѡ��Ҫ�޸ĵ���Ϣ��" << endl;
			cout << "\t\t1 ѧ��  2. ����  3. �Ա�  4. ��������  5. רҵ  6. �绰  7. ����  8. ����  9. ��ʦ" << endl;
			cout << "\t\t������ѡ��0-8��:";
			int choice;
			cin >> choice;

			string input;
			string year, month, day;
			switch (choice) {
			case 1:
				old_post_id = it->id;
				cout << "\t\t�������µ�ѧ�ţ�";
				cin >> input;
				it->id = input;
				post_id = it->id;
				accountSystem.acc_update(0);
				break;
				
			case 2:
				cout << "\t\t�������µ�������";
				cin >> input;
				it->name = input;
				break;
			case 3:
				cout << "\t\t�������µ��Ա�";
				cin >> input;
				it->gender = input;
				break;
			case 4:
				cout << "\t\t�������µĳ�����ݣ�";
				cin >> year;
				cout << "\t\t�������µĳ����·ݣ�";
				cin >> month;
				cout << "\t\t�������µĳ������ڣ�";
				cin >> day;
				it->change_birth(year, month, day);
				break;
			case 5:
				cout << "\t\t�������µ�רҵ��";
				cin >> input;
				it->major = input;
				break;
			case 6:
				cout << "\t\t�������µĵ绰��";
				cin >> input;
				it->phone_num = input;
				break;
			case 7:
				cout << "\t\t�������µ����䣺";
				cin >> input;
				it->email = input;
				break;
			case 8:
				cout << "\t\t�������µĿ��⣺";
				cin >> input;
				it->title = input;
				break;
			case 9:
				cout << "\t\t�������µĵ�ʦ��";
				cin >> input;
				it->tutor = input;
				break;
			default:
				cout << "\t\t��Чѡ��" << endl;
				break;
			}
			post_writefile();
			string option;
			cout << "\t\t����Ϣ�޸ĳɹ����Ƿ�����޸ģ���1 �� 0 ��" << endl;
			cout << "\t\t�����ѡ��0-1����";
			cin >> option;
			while (option != "0" && option != "1")
			{
				cout << "\t\t���벻�Ϸ�,������ѡ��0-1����";
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
		cout << "\t\tû���ҵ���ѧ�ŵ��о�����Ϣ��" << endl;
	}
	system("pause");
}

//�о�����Ϣ��ѯ����
void post_manager::post_find()
{
	system("cls");
	cout << "\t\t**********************��ѯ�о�����Ϣ*************************" << endl;
	cout << "\t\t������Ҫ��ѯ���о���ѧ�ţ�";
	string id;
	cin >> id;

	// ͨ��ѧ�Ų�ѯ
	auto it = std::find_if(postList.begin(), postList.end(), [&](postgraduate& p) {
		return p.id == id;
		});

	if (it != postList.end()) {
		cout << "\t\tѧ�ţ�" << it->id << endl;
		cout << "\t\t������" << it->name << endl;
		cout << "\t\t�Ա�" << it->gender << endl;
		cout << "\t\t�������ڣ�" << it->data_of_birth.get_year() << "-" << it->data_of_birth.get_month() << "-" << it->data_of_birth.get_day() << endl;
		cout << "\t\tרҵ��" << it->major << endl;
		cout << "\t\t�绰��" << it->phone_num<< endl;
		cout << "\t\t���䣺" << it->email << endl;
		cout << "\t\t���⣺" << it->title << endl;
		cout << "\t\t��ʦ��" << it->tutor << endl;
	}
	else {
		cout << "\t\tû���ҵ���ѧ�ŵ��о�����Ϣ��" << endl;
	}
	system("pause");
}

//�о�����Ϣ��չ���
void post_manager::post_clear()
{
	system("cls");
	cout << "\t\t**********************��������о�����Ϣ*************************" << endl;
	cout << "\t\t��ȷ��Ҫ��������о��������𣿣�1 �� 0 ��:";
	string choice;
	cin >> choice;

	if (choice == "1") {
		postList.clear();
		post_writefile();
		accountSystem.stu_clear(0);
		cout << "\t\t�����о�����Ϣ�ѳɹ���գ�" << endl;
	}
	else {
		cout << "\t\t������ȡ����" << endl;
	}
	system("pause");
}

//�о�����Ϣͳ�ƣ����򣩹���
void post_manager::post_sort()
{
	system("cls");
	cout << "\t\t**********************ͳ���о�������(����)*************************" << endl;
	cout << "\t\t��ѡ������ʽ��" << endl;
	cout << "\t\t1. ��ѧ������" << endl;
	cout << "\t\t2. ����������" << endl;
	cout << "\t\t������ѡ��1-2��:";
	string choice;
	cin >> choice;

	if (choice == "1") {
		// ͨ��ѧ������
		std::sort(postList.begin(), postList.end(), [](postgraduate& a, postgraduate& b) {
			return a.id < b.id;
			});
		cout << "\t\t��ѧ�������������£�" << endl;
		post_stuChart();

	}
	else if (choice == "2") {
		// ͨ����������
		std::sort(postList.begin(), postList.end(), [](postgraduate& a, postgraduate& b) {
			return a.name < b.name;
			});
		cout << "\t\t����������ĸ�������£�" << endl;
		post_stuChart();
	}
	else {
		cout << "\t\t��Чѡ��" << endl;
	}
	post_writefile();
	system("pause");
}

//չʾһλͬѧ����Ϣ
void post_manager::post_display_one(int i)
{
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << "ѧ��";
	cout << left << setw(10) << "����";
	cout << left << setw(5) << "�Ա�";
	cout << left << setw(20) << "רҵ";
	cout << left << setw(15) << "�о�����";
	cout << left << setw(10) << "��ʦ����";
	cout << left << setw(15) << "�绰����";
	cout << left << setw(18) << "��������";
	cout << left << setw(15) << "��������";
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

//�о�����Ϣչʾ����
void post_manager::post_display()
{
	system("cls");
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << "ѧ��";
	cout << left << setw(10) << "����";
	cout << left << setw(5) << "�Ա�";
	cout << left << setw(20) << "רҵ";
	cout << left << setw(15) << "�о�����";
	cout << left << setw(10) << "��ʦ����";
	cout << left << setw(15) << "�绰����";
	cout << left << setw(18) << "��������";
	cout << left << setw(15) << "��������";
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
	if (postList.size() == 0) cout << "\t\t\t\t\t\t��ǰ����ѧ��\n";
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	system("pause");
}

//ѧ����Ϣ����
void post_manager::post_stuChart() {

	cout << "\t\t---------------------------------------------------------------------------------" << endl;
	cout << "\t\t";
	cout << left << setw(15) << "ѧ��";
	cout << left << setw(10) << "����";
	cout << left << setw(5) << "�Ա�";
	cout << left << setw(20) << "רҵ";
	cout << left << setw(20) << "�о�����";
	cout << left << setw(10) << "��ʦ����" << endl;
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
	if (postList.empty()) cout << "\t\t\t\t\t\t��ǰ����ѧ��Ŷ~\n";
	cout << "\t\t---------------------------------------------------------------------------------" << endl;



}
