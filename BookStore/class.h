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

	void addBook() { //å �߰�
		string add_author, add_title;
		int add_price;

		cout << "�߰��� å�� ������ �Է��ϼ���." << endl;
		cout << "���� : ";
		cin >> add_title;
		cout << endl;
		cout << "�۰� : ";
		cin >> add_author;
		cout << endl;
		cout << "���� : ";
		cin >> add_price;

		ofstream fout;
		fout.open("info_book.txt", std::ios_base::out | std::ios_base::app);

		while (true) {
			fout << add_title << setw(10) << add_author << setw(10) << add_price << endl;
			cout << add_title << "��(��) ���������� �߰��Ǿ����ϴ�." << endl;
			break;
		}
		fout.close();
	}

	void showBook() { //��� å ��ȸ

		ifstream fin;
		fin.open("info_book.txt");
		cout << "-����-" << "          " << "-�۰�-" << "          " << "-����-" << endl;

		while (fin >> title >> author >> price) {
			cout << title << "         " << author << "           " << price << endl;
		}
		fin.close();
	}

	string searchBook() { //åã��
		string s_title, s_author, search, result;

		cout << "�˻� : ";
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
	int booknum=0; //��ٱ��� å ����
	string cart[30]; //��ٱ��� �迭

	int buynum = 0;
	string name[10];
	string address[10];
	string title[10];

public:
	void join() { //����
		cout << "���̵� �Է� >> ";
		cin >> id;
		cout << "��й�ȣ �Է� >> ";
		cin >> pw;

		ofstream fout;
		fout.open("info_user.txt", std::ios_base::out | std::ios_base::app);

		while (true) {
			fout << id << setw(10) << pw << endl;
			cout << id << "�� ���� ȯ���մϴ�." << endl;
			break;
		}
		fout.close();
	}

	int login() { //�α���
		ifstream fin;
		fin.open("info_user.txt");

		this->id = "";
		this->pw = "";

		string u_id, u_pw;
		int check = 0;

		cout << "���̵� �Է� >> ";
		cin >> u_id;
		cout << "��й�ȣ �Է� >> ";
		cin >> u_pw;

		while (fin >> id >> pw) {
			this->id = id;
			this->pw = pw;

			if (u_id == this->id && u_pw == this->pw) {
				cout << this->id << "�� ȯ���մϴ�." << endl;
				check = 1;
				break;
			}
			else {
				this->id = "";
				this->pw = "";
			}
		}

		if (this->id == "") {
			cout << "���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
		}

		fin.close();
		return check;
	}

	void buyBook(string buytitle) {
		string address;
		int num = 0;
		
		cout << "1.����  2.��ٱ���  3.��� " << endl;
		cin >> num;

		if (num == 1) { //����

			cout << "���� : ";
			cin >> this->name[buynum];
			cout << "����� : ";
			cin.ignore();
			getline(cin, address);
			this->title[buynum] = buytitle;
			this->address[buynum] = address;

			ofstream fout("receipt.txt");

			while (true) {
				for (int i = 0; i <= buynum; i++) {
					fout << endl;
					fout << "�̸� : " << this->name[i] << endl;
					fout << "����� : " << this->address[i] << endl;
					fout << "���� : " << this->title[i] << endl;
					fout << "===============" << endl;
				}
				break;
			}
			buynum += 1;
			cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
			fout.close();
		}
		else if (num == 2) { //��ٱ���
			ofstream fout("cart.txt");
			string title, author;
			int price;

			ifstream fin;
			fin.open("info_book.txt");
			string cartauthor;
			int cartprice;

			while (fin >> title >> author >> price) { //å���� �ش��ϴ� �۰��� ���� ��������
				if (buytitle == title) {
					cartauthor = author;
					cartprice = price;
				}
			}

			cart[booknum] = to_string(booknum+1) + ".  " + buytitle + "  " + cartauthor + "  " + to_string(cartprice) + "��"; //�ؽ�Ʈ�� ���� ����

			while (true) {
				for (int i = 0; i <= booknum; i++) {
					fout << cart[i] << endl;
				}
				break;
			}
			booknum += 1;
			cout << "��ٱ��Ͽ� �߰��߽��ϴ�." << endl;
			fout.close();
		}
		else if (num == 3) { //���
			cout << endl;
		}
	}

	void showReceipt() { //���ų��� Ȯ��
		ifstream fin;
		string in_line;
		fin.open("receipt.txt");
		cout << "=====" << this->id << "���� ���ų���=====" << endl;
		cout << endl;
		if(this->title[0]!="") {
			while (getline(fin, in_line)) {
				cout << in_line << endl;
			}
		}
		else {
			cout << "���ų����� �����ϴ�." << endl;
		}
		fin.close();
	}

	void showCart() { //��ٱ��� Ȯ��
		ifstream fin;
		string in_line;
		fin.open("cart.txt");

		cout << "=====" << this->id << "���� ��ٱ���=====" << endl;
		cout << endl;

		if (this->cart[0] != "") {
			while (getline(fin, in_line)) {
				cout << in_line << endl;
			}
		}
		else {
			cout << "��ٱ��ϰ� ����ֽ��ϴ�." << endl;
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

		cout << "������ �ڵ带 �Է��ϼ���." << endl;
		cin >> u_code;

		if (this->code == u_code) {

			cout << "���̵� �Է� >> ";
			cin >> id;
			cout << "��й�ȣ �Է� >> ";
			cin >> pw;

			ofstream fout;
			fout.open("info_manager.txt", std::ios_base::out | std::ios_base::app);

			while (true) {
				fout << id << setw(10) << pw << endl;
				cout << id << "�� ������ ������ �Ϸ�Ǿ����ϴ�." << endl;
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

		cout << "���̵� �Է� >> ";
		cin >> u_id;
		cout << "��й�ȣ �Է� >> ";
		cin >> u_pw;

		while (fin >> id >> pw) {
			this->id = id;
			this->pw = pw;

			if (u_id == this->id && u_pw == this->pw) {
				cout << this->id << "�� ȯ���մϴ�." << endl;
				check = 1;
				break;
			}
			else {
				this->id = "";
				this->pw = "";
			}
		}

		if (this->id == "") {
			cout << "���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
		}
		fin.close();
		return check;
	}

	void showUser() {
		ifstream fin;
		fin.open("info_user.txt");

		cout << "-���̵�-" << "          " << "-��й�ȣ-" << endl;
		while (fin >> id >> pw) {
			cout <<" " << id << "             " << pw << endl;
		}
		fin.close();
	}
};