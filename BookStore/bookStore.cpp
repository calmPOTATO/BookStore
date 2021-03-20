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

	int num = 0; //동작을 선택하는 변수
	int break_num = 0; //while문을 빠져나가기 위한 변수
	int login_check = 0; //로그인이 되었는지 판단하기 위한 변수
	string search = ""; //검색어를 저장하는 변수

	cout << "안녕하십니까. 원하는 서비스를 선택하세요." << endl;
	cout << "1. 사용자    2. 매니저" << endl;
	cin >> num;
	Sleep(500);
	system("cls");

	//사용자 모드
	if (num == 1) {
		while (true) {
			cout << "1. 회원가입 2. 로그인 3. 종료" << endl;
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
						//로그인 후 기능
						while (true) {
							cout << "1.도서검색/구매   2.구매내역   3.장바구니 보기   4.종료" << endl;
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
									cout << search << "없는 도서입니다. 다시 시도해주세요." << endl;
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
								cout << "서비스를 종료합니다. 이용해주셔서 감사합니다." << endl;
								exit(0);
							}
						}
					}
					else {
						break;
					}
				case 3:
					system("cls");
					cout << "서비스를 종료합니다. 이용해주셔서 감사합니다." << endl;
					exit(0);
			}
		}
	}

	//매니저모드
	else if (num == 2) {
		while (true) {
			cout << "1. 회원가입 2. 로그인 3. 종료" << endl;
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
					//로그인 후 기능
					while (true) {
						cout << "1. 도서추가  2. 도서조회  3. 회원조회  4. 종료" << endl;
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
							cout << "서비스를 종료합니다. 이용해주셔서 감사합니다." << endl;
							exit(0);
						}
					}
				}
				else {
					break;
				}
			case 3:
				system("cls");
				cout << "서비스를 종료합니다. 이용해주셔서 감사합니다." << endl;
				exit(0);
			}
		}
	}
	else {
		cout << "잘못된 선택입니다. 프로그램을 종료합니다." << endl;
	}

	return 0;
}

