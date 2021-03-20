#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "class.h"
#include <Windows.h>

using namespace std;


int main() {
	User u;
	Manager m;
	Book b;

	int num = 0; //������ �����ϴ� ����
	int break_num = 0; //while���� ���������� ���� ����
	int login_check = 0; //�α����� �Ǿ����� �Ǵ��ϱ� ���� ����
	string search = ""; //�˻�� �����ϴ� ����

	cout << "�ȳ��Ͻʴϱ�. ���ϴ� ���񽺸� �����ϼ���." << endl;
	cout << "1. �����    2. �Ŵ���" << endl;
	cin >> num;
	Sleep(500);
	system("cls");

	//����� ���
	if (num == 1) {
		while (true) {
			cout << "1. ȸ������ 2. �α��� 3. ����" << endl;
			cin >> num;

			switch (num) {
				case 1:
					u.join();
					Sleep(500);
					system("cls");
					continue;
				case 2:
					login_check = u.login();
					if (login_check == 1) {
						Sleep(500);
						system("cls");
						//�α��� �� ���
						while (true) {
							cout << "1.�����˻�/����   2.���ų���   3.��ٱ��� ����   4.����" << endl;
							cin >> num;
							switch (num) {
							case 1:
								search = b.searchBook();
								if (search != "") {
									u.buyBook(search);
									Sleep(400);
									system("cls");
								}
								else {
									cout << search << "���� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
									Sleep(500);
									system("cls");
								}
								break;
							case 2:
								u.showReceipt();
								Sleep(2000);
								system("cls");
								break;
							case 3:
								u.showCart();
								Sleep(2000);
								system("cls");
								break;
							case 4:
								break_num = 1;
								break;
							}
							if (break_num == 1) {
								system("cls");
								cout << "���񽺸� �����մϴ�. �̿����ּż� �����մϴ�." << endl;
								exit(0);
							}
						}
					}
					else {
						break;
					}
				case 3:
					system("cls");
					cout << "���񽺸� �����մϴ�. �̿����ּż� �����մϴ�." << endl;
					exit(0);
			}
		}
	}

	//�Ŵ������
	else if (num == 2) {
		while (true) {
			cout << "1. ȸ������ 2. �α��� 3. ����" << endl;
			cin >> num;

			switch (num) {
			case 1:
				m.join();
				Sleep(500);
				system("cls");
				continue;
			case 2:
				login_check = m.login();
				if (login_check == 1) {
					Sleep(500);
					system("cls");
					//�α��� �� ���
					while (true) {
						cout << "1. �����߰�  2. ������ȸ  3. ȸ����ȸ  4. ����" << endl;
						cin >> num;
						switch (num) {
						case 1:
							b.addBook();
							Sleep(700);
							system("cls");
							break;
						case 2:
							b.showBook();
							Sleep(2000);
							system("cls");
							break;
						case 3:
							m.showUser();
							Sleep(2000);
							system("cls");
							break;
						case 4:
							break_num = 1;
							break;
						}
						if (break_num == 1) {
							system("cls");
							cout << "���񽺸� �����մϴ�. �̿����ּż� �����մϴ�." << endl;
							exit(0);
						}
					}
				}
				else {
					break;
				}
			case 3:
				system("cls");
				cout << "���񽺸� �����մϴ�. �̿����ּż� �����մϴ�." << endl;
				exit(0);
			}
		}
	}
	else {
		cout << "�߸��� �����Դϴ�. ���α׷��� �����մϴ�." << endl;
	}

	return 0;
}

