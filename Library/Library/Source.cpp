#include<iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>   
#include <Windows.h>
#include <time.h>
#include <signal.h>
using namespace std;
/////////////////global variables///////
const int num = 100; const string space = "---------------";
char button[5];
bool success = 0;
int person_count = 0, curruser = -1;
char c, k;
////////////////structs/////////////////
struct borrowed {
	string bookName;
	int ID = 0;
	bool deleted = 0;
};
struct account {
	string username;
	string password;
	borrowed bookBorrowed[num] = { "" };
	int ID = 1;
	bool confirm = 0;
	int bookCounter = 0;
}person[100];
struct bookst
{
	int code = 0;
	string name;
	string category;
	string Author_Name;
	string edition;
	bool availablity = 0;
	bool borrowed = 0;
}book[num];
struct login
{
	string username;
	string password;
}login;
/////////////////functions//////////////
void getbooksdata();
void addnewbook();
void deletebook();
void editbook();
void mainmenu();
void admin();
void reviewcurrentbooks();
void updatefile();
void studentdata();
void adminsingin();
void studentedit();
int signin();
void pwinput(string&);
void reg();
void studentsignin();
void userInterface();
void showListOfBooks();
void showInformationOfBook(int);
void selectBookToShowInfo(int);
void selectBook(int);
void askUserForSelectOrModify();
void modifyBook();
void deleteOrder();
void returnBooks();
void deleteBookBorowed();
bool confirmOrder(char);
void getstudentacc();
void updatestudentfile();
void logout();
void invalidinput();
////////////////////////////////////////
int main()
{
	getstudentacc();
	getbooksdata();
	mainmenu();
	updatefile();
	updatestudentfile();
}
void mainmenu() {
	button[0] = '5';
	while (button[0] != '3')
	{
		cout << "1-Student\n2-Admin\n3-Exit\n";
		cout << "Enter 1 or 2 or 3\n";
		cin >> button[0]; cout << space << endl;
		switch (button[0]) {
		case '1':
		{
			////student
			curruser = -1;
			studentsignin();
			system("cls");
			userInterface();
			break;
		}
		case '2':
		{
			////admin
			system("cls");
			adminsingin();
			admin();
			break;
		}
		case '3': { updatefile(); updatestudentfile(); exit(1); }
		default:
		{
			cout << "You can only enter 1 or 2 or 3\n";
			break;
		}
		}
	}
}
void getbooksdata() {
	string line[4];
	fstream out_file;
	out_file.open("bookfile.txt");
	int counter = 0, counter2 = 1;
	while (!out_file.eof())
	{
		for (int i = 0; i < 4; i++)
		{
			getline(out_file, line[i]);

		}
		if (line[0] == "") {}
		else {
			book[counter2].name = line[0];
			book[counter2].category = line[1];
			book[counter2].Author_Name = line[2];
			book[counter2].edition = line[3];
			book[counter2].availablity = 1;
			book[counter2].code = counter2;
			counter2++;
		}
	}
	out_file.close();
}
void updatefile() {
	ofstream ofs;
	ofs.open("bookfile.txt", ofstream::out | ofstream::trunc);
	ofs.close();
	ofs.open("bookfile.txt");
	int last;
	for (int i = 0; i < num; i++) {
		if (book[i].availablity == 1) { last = i; }
	}
	for (int i = 0; i < num; i++) {
		if (book[i].availablity == 1 && i < last) {
			ofs << book[i].name << endl;
			ofs << book[i].category << endl;
			ofs << book[i].Author_Name << endl;
			ofs << book[i].edition << endl;
		}
	}
	ofs << book[last].name << endl;
	ofs << book[last].category << endl;
	ofs << book[last].Author_Name << endl;
	ofs << book[last].edition;
	ofs.close();
}
void admin() {
	button[1] = '9';
	while (button[1] != '5' && button[1] != '6')
	{
		cout << "1-Add new book\n2-Delete a book\n3-Edit";
		cout << "\n4-Review\n5-Back\n6-Exit\n";
		cin >> button[1];
		system("cls");
		switch (button[1]) {
		case '1':
		{
			//Can add new book
			addnewbook();
		}
		break;
		case '2':
		{
			//Can delete any book.
			deletebook();
		}
		break;
		case '3':
		{
			// Can modify some information about any book
			editbook();
		}
		break;
		case '4':
		{
			// review the current books
			reviewcurrentbooks();
		}
		break;
		case '5':
		{
			////back
			mainmenu();
		}
		break;
		case '6':
		{
			////exit
			updatestudentfile();
			updatefile();
			exit(1);
		}
		break;
		default: {
			invalidinput();
			break; }
		}
	}
}
void reviewcurrentbooks() {
	for (int i = 0; i < num; i++)
	{
		if (book[i].availablity == 1)
		{
			cout << "Code: " << book[i].code << endl;
			cout << "Name: " << book[i].name << endl;
			cout << "Category: " << book[i].category << endl;
			cout << "Author name: " << book[i].Author_Name << endl;
			cout << "Edition: " << book[i].edition << endl << space << endl;
		}
	}
}
void addnewbook() {
	char confirm;
	string input[4] = { "" };
	cout << "Add new book\n";
	getline(cin, input[0]);
	cout << "Enter book's name: ";
	getline(cin, input[0]);
	cout << "Enter the category: ";
	getline(cin, input[1]);
	cout << "Enter Author Name: ";
	getline(cin, input[2]);
	cout << "Enter the edition: ";
	getline(cin, input[3]);
	for (int i = 1; i < num; i++)
	{
		if (book[i].availablity == 0)
		{
			cout << "To confirm adding this book enter 'y' ";
			cin >> confirm;
			if (confirm == 'y' || confirm == 'Y')
			{
				system("cls");
				cout << "A new book has been added successfully\n" << space << endl;
				book[i].name = input[0];
				book[i].category = input[1];
				book[i].Author_Name = input[2];
				book[i].edition = input[3];
				book[i].availablity = 1;
				book[i].code = i;
				break;
			}
			else {
				system("cls");
				cout << "No book has been added\n" << space << endl;
				break;
			}

		}
	}
}
void deletebook() {
	system("cls");
	int choose, last;
	char confirm;
	for (int i = 0; i < num; i++)
	{
		if (book[i].availablity == 1) {
			cout << book[i].code << "- " << book[i].name << endl;
			last = book[i].code;
		}
	}
	cout << "Enter the book number to delete it\nor enter 0 to back  ";
	cin >> choose;
	if (!choose) {
		cin.clear();
		cin.ignore(100, '\n');
		system("cls");
		cout << "invalid input!\nNo book has been deleted\n" << space << endl;
		return;
	}
	if (choose <= last)
	{
		for (int i = 0; i < num; i++) {
			if (choose == i) {
				cout << "Enter 'y' to confirm deleting this book ";
				cin >> confirm;
				if (confirm == 'y' || confirm == 'Y') {
					book[i].availablity = 0;
					system("cls");
					cout << "\nThe book has been deleted successfully\n" << space << endl;
					updatefile();
					getbooksdata();
					break;
				}
				else {
					system("cls");
					cout << "No book has been deleted\n" << space << endl;
				}
			}
		}

	}
	else {
		system("cls");
		cout << "No book has been deleted\n" << space << endl;

	}
}
void editbook() {
	int choose, choose2 = 0, last;
	char a = 'h', b = 'y';
	/////view books
	system("cls");
	for (int i = 0; i < num; i++)
	{
		if (book[i].availablity == 1) {
			cout << book[i].code << "- " << book[i].name << endl;
			last = book[i].code;
		}
	}

	cout << "\nEnter the book number to edit it\nor enter 0 to back  ";
	cin >> choose;
	if (!choose) {
		cin.clear();
		cin.ignore(100, '\n');
		int op;
		cout << "invalid input\n";
		cout << "1- Try another number\n2- Back\nEnter 1 or 2\n";
		cin >> op;
		if (!op) {
			invalidinput();
		}
		if (op == 1) {
			system("cls");
			editbook();
		}
		else {
			system("cls");
			admin();
		}
	}
	if (choose <= last && choose > -1) {
		while (b == 'y') {///////////////////
			system("cls");
			cout << "1- Name: " << book[choose].name << endl;
			cout << "2- Category: " << book[choose].category << endl;
			cout << "3- Author name: " << book[choose].Author_Name << endl;
			cout << "4- Edition: " << book[choose].edition << endl;
			cout << "5-save and back\n";
			cout << "What do you want to edit?\nenter a number: ";
			cin >> choose2;
			if (!choose2) {
				invalidinput();
			}
			switch (choose2) {//////
			case 1: {cout << "Enter the new name: "; cin >> book[choose].name; break; }
			case 2: {cout << "Enter the new category: "; cin >> book[choose].category; break; }
			case 3: {cout << "Enter the new Author Name: "; cin >> book[choose].Author_Name; break; }
			case 4: {cout << "Enter the new edition: "; cin >> book[choose].edition; break; }
			case 5: {editbook(); break; }
			default: {cout << endl;  continue; }
				   a = 'y';
			}//////
			cout << "Do you want to continue editing this book?\ny/n  ";
			cin >> b;
			if (b == 'y' || b == 'Y') { system("cls"); b = 'y'; }
			else { system("cls"); cout << "your changes have been saved\n"; }
		}//////////////
	}
	else {
		button[2] = 3;
		cout << "1- Try another number\n2- Back\nEnter 1 or 2\n";
		while (button[2] != 1 && button[2] != 2) {
			cin >> button[2];
			switch (button[2])
			{
			case '1': {
				system("cls");
				editbook();
				admin();
			}break;
			case '2': {
				system("cls");
				admin(); }
					break;
			default: {cout << "Invalid option"; }
				   break;
			}

		}
	}

}
void adminsingin()
{
	cout << "1.login\n";
	cout << "------------------------\n";
	//  curruser = signin();
	account acc;
	cout << "Username: ";
	cin >> acc.username;
	cout << "\nPassword: ";
	pwinput(acc.password);

	if (acc.password == "123456789") {
		cout << "\033[2J\033[1;1H";
		cout << "Welcome, " << acc.username << "!\n";
		admin();
	}
	else
		cout << "\033[2J\033[1;1H";
	cout << "1.try again\n";
	cout << "2.back\n";

	cin >> k;
	if (k == '1') {
		cout << "\033[2J\033[1;1H";
		adminsingin();
	}

	if (k == '2') {
		cout << "\033[2J\033[1;1H";
		mainmenu();

	}
	else {
		cout << "invalid option\n";
	}

}
void studentsignin() {
	if (curruser == -1) {
		cout << "Welcome!\n";
		cout << "------------------------\n";
		cout << "\033[2J\033[1;1H";
		cout << "1.register\n";
		cout << "2.login\n";

		cin >> k;
		if (k == '1') {
			cout << "\033[2J\033[1;1H";
			reg();
		}

		if (k == '2') {
			cout << "\033[2J\033[1;1H";

			curruser = signin();
			return;
		}
		else {
			cout << "invalid option\n";
		}
	}

	studentsignin();
}
void reg() {
	account acc;
	bool unique = 1;
	//char pw = '0';
	string confirm;
	acc.password = "";
	cout << "Username: ";
	cin >> acc.username;

	for (int i = 0; i < person_count; i++) {
		if (acc.username == person[i].username) {
			cout << "Username taken!\n";
			unique = 0;
			reg();
		}
	}
	if (unique) {
		cout << "\nPassword: ";
		pwinput(acc.password);
		cout << "\nConfirm Password: ";
		pwinput(confirm);

		if (acc.password != confirm) {

			cout << "1.try again\n";
			cout << "2.back\n";

			cin >> k;
			if (k == '1') {
				cout << "\033[2J\033[1;1H";
				reg();
			}

			if (k == '2') {
				cout << "\033[2J\033[1;1H";
				mainmenu();

			}
			else {
				cout << "invalid option\n";
			}

		}
		person[person_count] = acc, person_count++;
	}
	return;
}
int signin() {
	//char pw;
	account acc;
	cout << "Username: ";
	cin >> acc.username;
	cout << "\nPassword: ";
	pwinput(acc.password);

	for (int i = 0; i < person_count; i++) {
		if (acc.username == person[i].username && acc.password == person[i].password) {
			cout << "\033[2J\033[1;1H";
			cout << "Welcome, " << acc.username << "!\n";
			return i;//رجع الاندكس يعرف انا في اني اكاونت دلوقتي 
		}
	}
	cout << "Wrong Username/Password, please try again\n";
	//signin();
	cout << "\033[2J\033[1;1H";
	cout << "1.try again\n";
	cout << "2.back\n";

	cin >> k;
	if (k == '1') {
		cout << "\033[2J\033[1;1H";
		signin();
	}

	if (k == '2') {
		cout << "\033[2J\033[1;1H";
		mainmenu();

	}
	else {
		cout << "invalid option\n";
	}





}
void pwinput(string& pw) {
	char input = '0';
	do {
		input = _getch();
		if (input == '\b') {
			if (!pw.empty()) {
				pw.pop_back();
				cout << "\b \b";
			}
		}
		else if (input != '\r') {
			pw += input;
			cout << '*';
		}
		else if (pw.size() < 6) {
			cout << "\nPassword is too short, minimum 6 characters, try again\n";

			pw.clear();

			input = '0';

			cout << "password:";

		}

	} while (input != '\r');

	cout << '\n';
	return;
}
void studentedit() {
	string new_username;
	account acc;
	bool test = 1, test2 = 1;
	cout << "\033[2J\033[1;1H";
	cout << "1. change username\n";
	cout << "2. change password\n";
	cin >> c;
	if (c == '1') {
		cout << "new username: ";
		cin >> new_username;
		for (int i = 0; i < person_count; i++) {

			if (new_username == person[i].username) {
				test2 = 0;
				break;
			}
		}
		if (test2) {
			system("cls");
			person[curruser].username = new_username;
			curruser = -1;
			cout << "usernamed changed successfully\n" << space << endl;
		}
		else {
			system("cls");
			cout << "username taken\n";
			int op = 3;
			while (op != 1 && op != 2) {
				cout << "1- Try again\n2- Back\nEnter 1 or 2\n";
				cin >> op;
				if (!op) {
					invalidinput();
				}
				if (op == 1) {
					system("cls");
					studentedit();
				}
				if (op == 2) {
					system("cls");
					break;
				}
			}
		}
	}
	else if (c == '2') {
		cout << "new password: ";
		person[curruser].password = "";
		pwinput(person[curruser].password);
		cout << "\033[2J\033[1;1H";
		curruser = -1;
		cout << "password changed successfully\n" << space << endl;
	}
	else {
		cout << "Invalid input\n";
		studentedit();
	}
}
void userInterface() {
	int choice;
	cout << "1-View list of books name\n2-Edit Your Information\n3-Check out your order\n";
	cout << "4-Return books you borrowed\n5-Log out\n";
	cout << "Enter 1 or 2 or 3 or 4 or 5 \n";
	cin >> choice;
	if (!choice) {
		invalidinput();
	}
	switch (choice)
	{
	case 1:
		//view list of books
		system("cls");
		showListOfBooks();
		break;
	case 2:
		//edit
		system("cls");
		studentedit();
		break;
	case 3:
		//check out
		system("cls");
		modifyBook();
		break;
	case 4:
		//return books
		returnBooks();
		break;
	case 5:
		//log out
		system("cls");
		logout();
		mainmenu();
		break;
	default:
		system("cls");
		cout << "You can only enter 1 or 2 or 3 or 4 or 5\n";
		userInterface();
		break;
	}
}
void showListOfBooks() {
	int index = 1;
	for (int i = 0; i < num; i++) {
		if (book[i].availablity == 1) {
			cout << index << "-" << book[i].name;
			if (book[i].borrowed == 1)
				cout << " [NOT AVAILABLE]";
			cout << "\n";
			index++;
		}
	}
	selectBookToShowInfo(--index);
}
void selectBookToShowInfo(int index) {
	int numOfBook;
	cout << space << "\n";
	while (true) {
		cout << "Enter the book number to show its Data\nOr enter -1 to back\n";
		cin >> numOfBook;
		if (!numOfBook) {
			cin.clear();
			cin.ignore(100, '\n');
			int op;
			cout << "invalid input\n";
			cout << "1- Try another number\n2- Back\nEnter 1 or 2\n";
			cin >> op;
			if (!op) {
				invalidinput();
			}
			if (op == 1) {
				system("cls");
				showListOfBooks();
			}
			else {
				system("cls");
				userInterface();
			}

		}
		if (numOfBook == -1) {
			system("cls");
			userInterface();
		}
		else if (numOfBook <= index) {
			showInformationOfBook(numOfBook);
		}
		else {
			cout << "INVALIDE CHOICE!\n";
		}
	}
}
void showInformationOfBook(int numOfBook) {
	system("cls");
	cout << "ID: " << book[numOfBook].code << "\n";
	cout << "Name: " << book[numOfBook].name << "\n";
	cout << "Category: " << book[numOfBook].category << "\n";
	cout << "Author name: " << book[numOfBook].Author_Name << "\n";
	if (book[numOfBook].edition != "")
		cout << "Edition: " << book[numOfBook].edition << "\n";
	selectBook(numOfBook);
}
void selectBook(int numOfBook) {
	int choice;
	char ch;
	if (book[numOfBook].borrowed == 1) {
		while (true) {
			cout << space << "\n";
			cout << "Enter -1 to back\n";
			cin >> choice;
			if (!choice) {
				invalidinput();
			}
			if (choice == -1) {
				system("cls");
				showListOfBooks();
			}
			else
				cout << "INVALID CHOICE!\n";
		}
	}
	else {
		while (true) {
			cout << space << "\n";
			cout << "1-Borrow this book\n2-Check out your order\n3-back\n";
			cout << "Enter 1 or 2 or 3\n";
			cin >> choice;
			if (!choice) {
				invalidinput();
			}
			switch (choice) {
			case 1:
				//borrow
				cout << "To confirm borrowing this book enter 'y'";
				cin >> ch;
				if (ch == 'y' || ch == 'Y') {
					person[curruser].bookBorrowed[person[curruser].bookCounter].ID = book[numOfBook].code;
					person[curruser].bookBorrowed[person[curruser].bookCounter].bookName = book[numOfBook].name;
					book[numOfBook].borrowed = 1;
					person[curruser].bookCounter++;
					system("cls");
					askUserForSelectOrModify();
				}
				else {
					system("cls");
					showListOfBooks();
				}
				break;
			case 2:
				//check out 
				system("cls");
				modifyBook();
				break;
			case 3:
				//back
				system("cls");
				showListOfBooks();
				break;
			default:
				cout << "You can only enter 1 or 2 or 3\n";
				break;
			}
		}
	}
}
void askUserForSelectOrModify() {
	int choice;
	cout << "1-View list of books\n2-Check out your order\n3-Back to first page\n";
	cout << "Enter 1 or 2 or 3\n";
	cin >> choice;
	if (!choice) {
		invalidinput();
	}
	system("cls");
	switch (choice)
	{
	case 1:
		//view list of book
		showListOfBooks();
		break;
	case 2:
		//check out
		modifyBook();
		break;
	case 3:
		//back
		userInterface();
		break;
	default:
		cout << "You can only enter 1 or 2\n";
		cout << space << "\n";
		askUserForSelectOrModify();
		break;
	}
}
void modifyBook() {
	int k, choice;
	char ch;
	cout << "1-Delete book from order\n2-View list of books";
	cout << "\n3-Confirm your order\n4-Delete your order\n5-Back\n6-Log out\n";
	cout << "Enter 1 or 2 or 3 or 4 or 5 or 6\n";
	cin >> choice;
	if (!choice) {
		invalidinput();
	}
	switch (choice)
	{
	case 1:
		//delete
		system("cls");
		for (int i = 0; i < person[curruser].bookCounter; i++) {
			if (person[curruser].bookBorrowed[i].deleted == 0) {
				cout << person[curruser].bookBorrowed[i].bookName;
				cout << " [" << person[curruser].bookBorrowed[i].ID << "] \n";
			}
		}
		cout << space << "\n";
		deleteBookBorowed();
		break;
	case 2:
		//view list 
		system("cls");
		showListOfBooks();
		break;
	case 3:
		//confirm
		k = 1;
		system("cls");
		cout << "Username: " << person[curruser].username << "\n";
		cout << "ID: " << person[curruser].ID << "\n";
		cout << "Your order: " << "\n";
		for (int i = 0; i < person[curruser].bookCounter; i++) {
			if (person[curruser].bookBorrowed[i].deleted == 0) {
				cout << k << "-" << person[curruser].bookBorrowed[i].bookName << "\n";
				k++;
			}
		}
		cout << space << "\n";
		if (person[curruser].confirm) {
			cout << "Your order is confirmed!\n";
			cout << "Press enter to back.....\n";
			cin.get();
			cin.ignore();
			system("cls");
			modifyBook();
		}
		else {
			cout << "Do you want to confirm this order(y/n)\n";
			cin >> ch;
			person[curruser].confirm = confirmOrder(ch);
			system("cls");
			modifyBook();
		}
		break;
	case 4:
		//delete all order
		deleteOrder();
		break;
	case 5:
		//back
		system("cls");
		userInterface();
		break;
	case 6:
		//log out
		system("cls");
		logout();
		mainmenu();
		break;
	default:
		cout << "You can only enter 1 or 2 or 3 or 4 or 5 or 6\n";
		modifyBook();
		break;
	}
}
void deleteBookBorowed() {
	int number;
	bool found = 0;
	char ch;
	cout << "Enter the book ID to delete it\nOr -1 to back\n";
	cin >> number;
	if (!number) {
		invalidinput();
	}
	if (number == -1) {
		system("cls");
		modifyBook();
	}
	else {
		for (int i = 0; i < person[curruser].bookCounter; i++) {
			if (number == person[curruser].bookBorrowed[i].ID)
				found = 1;
		}
		if (found) {
			cout << "To confirm deleting this book, enter 'y'";
			cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				for (int i = 0; i < num; i++) {
					if (number == book[i].code)
						book[i].borrowed = 0;
				}
				for (int i = 0; i < person[curruser].bookCounter; i++) {
					if (number == person[curruser].bookBorrowed[i].ID) {
						person[curruser].bookBorrowed[i].deleted = 1;
					}
				}
				system("cls");
				cout << "Book Deleted from order successfully\n";
				cout << space << "\n";
			}
			else {
				system("cls");
				cout << "No book has been deleted\n";
				cout << space << "\n";
			}
		}
		else {
			cout << "INVALIED CHOICE!\n";
			deleteBookBorowed();
		}
		modifyBook();
	}
}
bool confirmOrder(char ch) {
	system("cls");
	if (ch == 'Y' || ch == 'y') {
		cout << "Your order confirmed successfully\n";
		cout << "Press enter to continue.....\n";
		cin.get();
		cin.ignore();
		system("cls");
		return 1;
	}
	else {
		cout << "your order not confirmed\n";
		cout << "Press enter to back.....\n";
		cin.get();
		cin.ignore();
		system("cls");
		return 0;
	}
}
void returnBooks() {
	int k = 1;
	char ch;
	system("cls");
	if (person[curruser].confirm) {
		cout << "Username: " << person[curruser].username << "\n";
		cout << "ID: " << person[curruser].ID << "\n";
		cout << "Books you borrowed:\n";
		for (int i = 0; i < (person[curruser].bookCounter - 1); i++) {
			cout << k << "-" << person[curruser].bookBorrowed[i].bookName << "\n";
			k++;
		}
		cout << space << "\n";
		cout << "Do you want to return books you borrowed? (y/n)\n";
		cin >> ch;
		if (ch == 'Y' || ch == 'y') {
			for (int j = 0; j < person[curruser].bookCounter; j++) {
				for (int i = 0; i < num; i++) {
					if (person[curruser].bookBorrowed[j].bookName == book[i].name)
						book[i].borrowed = 0;
				}
			}
			for (int i = 0; i < num; i++) {
				person[curruser].bookBorrowed[i].deleted = 0;
			}
			person[curruser].confirm = 0;
			person[curruser].bookCounter = 0;
			system("cls");
			cout << "Books you borrowed returned successfully\n";
			cout << "Press enter to back.....\n";
			cin.get();
			cin.ignore();
			system("cls");
			userInterface();
		}
		else {
			system("cls");
			cout << "Books you borrowed not returned\n";
			cout << "Press enter to back.....\n";
			cin.get();
			cin.ignore();
			system("cls");
			userInterface();
		}
	}
	else {
		cout << "You've never borrowed books before!\n";
		cout << "Press enter to back.....\n";
		cin.get();
		cin.ignore();
		system("cls");
		userInterface();
	}
}
void deleteOrder() {
	char ch;
	system("cls");
	if (person[curruser].confirm) {
		cout << "Do you want to delete all your order?(y/n)\n";
		cin >> ch;
		if (ch == 'Y' || ch == 'y') {
			for (int j = 0; j < person[curruser].bookCounter; j++) {
				for (int i = 0; i < num; i++) {
					if (person[curruser].bookBorrowed[j].bookName == book[i].name)
						book[i].borrowed = 0;
				}
			}
			for (int i = 0; i < num; i++) {
				person[curruser].bookBorrowed[i].deleted = 0;
			}
			person[curruser].confirm = 0;
			person[curruser].bookCounter = 0;
			system("cls");
			cout << "Your order deleted successfully\n";
			cout << "Press enter to continue.....\n";
			cin.get();
			cin.ignore();
			system("cls");
			userInterface();
		}
		else {
			system("cls");
			cout << "Your order not deleted\n";
			cout << "Press enter to back.....\n";
			cin.get();
			cin.ignore();
			system("cls");
			modifyBook();
		}
	}
	else {
		cout << "You don't have any order!\n";
		cout << "Press enter to back.....\n";
		cin.get();
		cin.ignore();
		system("cls");
		modifyBook();
	}
}
void studentdata() {
	system("cls");
	int k;
	for (int i = 0; i < person_count; i++) {
		k = 1;
		cout << "Username: " << person[i].username << "\n";
		cout << "ID: " << person[i].ID << "\n";
		cout << "Books borrowed:\n";
		if (person[i].confirm == 1) {
			for (int j = 0; j < person[i].bookCounter; j++) {
				cout << k << "-" << person[i].bookBorrowed[j].bookName << "\n";
				k++;
			}
		}
		else {
			cout << "NO BOOKS BORROWED!\n";
		}
		cout << space << "\n";
	}
	admin();
}
void getstudentacc() {
	string line[2];
	fstream out_file2;
	out_file2.open("studentAccount.txt");
	while (!out_file2.eof())
	{
		for (int i = 0; i < 2; i++)
		{
			getline(out_file2, line[i]);
		}
		if (line[0] == "") {}
		else {
			person[person_count].username = line[0];
			person[person_count].password = line[1];
			person[person_count].ID = person_count;
			person_count++;
		}
	}
	out_file2.close();
}
void updatestudentfile() {
	ofstream read;
	read.open("studentAccount.txt", ofstream::out | ofstream::trunc);
	read.close();
	read.open("studentAccount.txt");
	for (int i = 0; i < num; i++) {
		if (person[i].username != "") {
			read << person[i].username << "\n";
			read << person[i].password << "\n";
		}
	}
	read.close();
}
void logout() {
	if (!person[curruser].confirm) {
		for (int j = 0; j < person[curruser].bookCounter; j++) {
			for (int i = 0; i < num; i++) {
				if (person[curruser].bookBorrowed[j].bookName == book[i].name)
					book[i].borrowed = 0;
			}
		}
		for (int i = 0; i < num; i++) {
			person[curruser].bookBorrowed[i].deleted = 0;
		}
		person[curruser].bookCounter = 0;
	}
}
void invalidinput() {
	system("cls");
	cout << "an eror occurred ( invalid input )\n\nrestart your program\n";
	updatefile();
	updatestudentfile();
	exit(0);
}