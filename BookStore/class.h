#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Book {
private:
	string title;
	string author;
	int price;

public:

	void addBook() { //책 추가
		string add_author, add_title;
		int add_price;

		cout << "추가할 책의 정보를 입력하세요." << endl;
		cout << "제목 : ";
		cin >> add_title;
		cout << endl;
		cout << "작가 : ";
		cin >> add_author;
		cout << endl;
		cout << "가격 : ";
		cin >> add_price;

		ofstream fout;
		fout.open("info_book.txt", std::ios_base::out | std::ios_base::app);

		while (true) {
			fout << add_title << setw(10) << add_author << setw(10) << add_price << endl;
			cout << add_title << "이(가) 성공적으로 추가되었습니다." << endl;
			break;
		}
		fout.close();
	}

	void showBook() { //모든 책 조회

		ifstream fin;
		fin.open("info_book.txt");
		cout << "-제목-" << "          " << "-작가-" << "          " << "-가격-" << endl;

		while (fin >> title >> author >> price) {
			cout << title << "         " << author << "           " << price << endl;
		}
		fin.close();
	}

	string searchBook() { //책찾기
		string s_title, s_author, search, result;

		cout << "검색 : ";
		cin >> search;
		cout << endl;

		ifstream fin;
		fin.open("info_book.txt");

		while (fin >> title >> author >> price) {
			s_title = title;
			s_author = author;

			if (search == s_title) {
				cout << title << "\t" << author << "\t" << price << endl;
				result = title;
			}
			else if (search == s_author) {
				cout << title << "\t" << author << "\t" << price << endl;
				result = title;
			}
		}
		fin.close();
		return result;
	}
};

class User {
private:
	string id;
	string pw;
	int booknum=0; //장바구니 책 개수
	string cart[30]; //장바구니 배열

	int buynum = 0;
	string name[10];
	string address[10];
	string title[10];

public:
	void join() { //가입
		cout << "아이디 입력 >> ";
		cin >> id;
		cout << "비밀번호 입력 >> ";
		cin >> pw;

		ofstream fout;
		fout.open("info_user.txt", std::ios_base::out | std::ios_base::app);

		while (true) {
			fout << id << setw(10) << pw << endl;
			cout << id << "님 가입 환영합니다." << endl;
			break;
		}
		fout.close();
	}

	int login() { //로그인
		ifstream fin;
		fin.open("info_user.txt");

		this->id = "";
		this->pw = "";

		string u_id, u_pw;
		int check = 0;

		cout << "아이디 입력 >> ";
		cin >> u_id;
		cout << "비밀번호 입력 >> ";
		cin >> u_pw;

		while (fin >> id >> pw) {
			this->id = id;
			this->pw = pw;

			if (u_id == this->id && u_pw == this->pw) {
				cout << this->id << "님 환영합니다." << endl;
				check = 1;
				break;
			}
			else {
				this->id = "";
				this->pw = "";
			}
		}

		if (this->id == "") {
			cout << "아이디 혹은 비밀번호를 틀렸습니다." << endl;
		}

		fin.close();
		return check;
	}

	void buyBook(string buytitle) {
		string address;
		int num = 0;
		
		cout << "1.구매  2.장바구니  3.취소 " << endl;
		cin >> num;

		if (num == 1) { //구매

			cout << "성함 : ";
			cin >> this->name[buynum];
			cout << "배송지 : ";
			cin.ignore();
			getline(cin, address);
			this->title[buynum] = buytitle;
			this->address[buynum] = address;

			ofstream fout("receipt.txt");

			while (true) {
				for (int i = 0; i <= buynum; i++) {
					fout << endl;
					fout << "이름 : " << this->name[i] << endl;
					fout << "배송지 : " << this->address[i] << endl;
					fout << "제목 : " << this->title[i] << endl;
					fout << "===============" << endl;
				}
				break;
			}
			buynum += 1;
			cout << "구매가 완료되었습니다." << endl;
			fout.close();
		}
		else if (num == 2) { //장바구니
			ofstream fout("cart.txt");
			string title, author;
			int price;

			ifstream fin;
			fin.open("info_book.txt");
			string cartauthor;
			int cartprice;

			while (fin >> title >> author >> price) { //책제목에 해당하는 작가랑 가격 가져오기
				if (buytitle == title) {
					cartauthor = author;
					cartprice = price;
				}
			}

			cart[booknum] = to_string(booknum+1) + ".  " + buytitle + "  " + cartauthor + "  " + to_string(cartprice) + "원"; //텍스트에 넣을 내용

			while (true) {
				for (int i = 0; i <= booknum; i++) {
					fout << cart[i] << endl;
				}
				break;
			}
			booknum += 1;
			cout << "장바구니에 추가했습니다." << endl;
			fout.close();
		}
		else if (num == 3) { //취소
			cout << endl;
		}
	}

	void showReceipt() { //구매내역 확인
		ifstream fin;
		string in_line;
		fin.open("receipt.txt");
		cout << "=====" << this->id << "님의 구매내역=====" << endl;
		cout << endl;
		if(this->title[0]!="") {
			while (getline(fin, in_line)) {
				cout << in_line << endl;
			}
		}
		else {
			cout << "구매내역이 없습니다." << endl;
		}
		fin.close();
	}

	void showCart() { //장바구니 확인
		ifstream fin;
		string in_line;
		fin.open("cart.txt");

		cout << "=====" << this->id << "님의 장바구니=====" << endl;
		cout << endl;

		if (this->cart[0] != "") {
			while (getline(fin, in_line)) {
				cout << in_line << endl;
			}
		}
		else {
			cout << "장바구니가 비어있습니다." << endl;
		}
		fin.close();
	}

};




class Manager {
private:
	string id;
	string pw;
	int code = 1234;

public:
	void join() {
		int u_code;

		cout << "관리자 코드를 입력하세요." << endl;
		cin >> u_code;

		if (this->code == u_code) {

			cout << "아이디 입력 >> ";
			cin >> id;
			cout << "비밀번호 입력 >> ";
			cin >> pw;

			ofstream fout;
			fout.open("info_manager.txt", std::ios_base::out | std::ios_base::app);

			while (true) {
				fout << id << setw(10) << pw << endl;
				cout << id << "님 관리자 가입이 완료되었습니다." << endl;
				break;
			}
			fout.close();
		}
	}

	int login() {

		ifstream fin;
		fin.open("info_manager.txt");

		this->id = "";
		this->pw = "";

		string u_id, u_pw;
		int check = 0;

		cout << "아이디 입력 >> ";
		cin >> u_id;
		cout << "비밀번호 입력 >> ";
		cin >> u_pw;

		while (fin >> id >> pw) {
			this->id = id;
			this->pw = pw;

			if (u_id == this->id && u_pw == this->pw) {
				cout << this->id << "님 환영합니다." << endl;
				check = 1;
				break;
			}
			else {
				this->id = "";
				this->pw = "";
			}
		}

		if (this->id == "") {
			cout << "아이디 혹은 비밀번호를 틀렸습니다." << endl;
		}
		fin.close();
		return check;
	}

	void showUser() {
		ifstream fin;
		fin.open("info_user.txt");

		cout << "-아이디-" << "          " << "-비밀번호-" << endl;
		while (fin >> id >> pw) {
			cout <<" " << id << "             " << pw << endl;
		}
		fin.close();
	}
};