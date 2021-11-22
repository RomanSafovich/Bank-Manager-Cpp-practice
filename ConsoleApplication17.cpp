// ConsoleApplication17.cpp : Defines the entry point for the console application.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

enum Choice {OPEN_ACCOUNT = 1, BALANCE_ENQUIRY, DEPOSIT, WITHDRAWAL,
				CLOSE_ACCOUNT, SHOW_ALL_ACCOUNTS, QUIT};


class Account
{
private:
	string firstName, lastName;
	int balance;
	int static count;
	int accountNum;
public:
	Account();
	Account(string firstName, string lastName, int balance);
	friend ofstream & operator<<(ofstream & ofs, Account &acc);
	friend ostream & operator<<(ostream &os, Account &acc);
	friend ifstream & operator>>(ifstream & ifs, Account &acc);
	int getAccountNum();
	int getBalance();
	void setCount(int count);
	int getCount();
	void setFirstName(string firstName);
	void setlastName(string lastName);
	void setBalance(int balance);
	string getFirstName();
	string getLastName();
};

ofstream & operator<<(ofstream & ofs, Account &acc)
{
	ofs << acc.getFirstName() <<" "<<  acc.getLastName() << " " << acc.getBalance() << " " << acc.getAccountNum() << endl;
	return ofs;
}

void Account::setCount(int count) { this->count = count; }

int Account::getCount() { return count; }

ostream & operator<<(ostream & os, Account &acc)
{
	os << "\nFirst Name: " << acc.firstName << endl;
	os << "Last Name: " << acc.lastName << endl;
	os << "Account Number: " << acc.accountNum << endl;
	os << "Balance: " << acc.balance << endl;
	os << "\n";
	return os;

}


ifstream & operator>> (ifstream &ifs, Account &acc) {
	ifs >> acc.firstName  >> acc.lastName  >> acc.balance  >> acc.accountNum;
	return ifs;
}
int Account::getBalance()
{
	return balance;
}

string Account::getFirstName()
{
	return firstName;
}

void Account::setFirstName(string firstName) { this->firstName = firstName; }
void Account::setlastName(string lastName) { this->lastName = lastName; }
void Account::setBalance(int balance) { this->balance = balance; }

string Account::getLastName() { return lastName; }
int Account::getAccountNum() { return accountNum; }
Account::Account(string firstName, string lastName, int balance)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->balance = balance;
	count++;
	accountNum = count;
}
Account::Account() {}

int Account::count = 0;

class Bank {
private:
	map<int, Account> accounts;
public:
	Bank();
	void createAccount(string firstName, string lastName, int balance);
	Account balanceEnquiry(int accountNum);
	void deposit(int accountNum, int balance);
	void withdrawal(int accountNum, int balance);
	map<int, Account> getAccounts();
	void showAllAccounts();
	void closeAccount(int acountNum);
	~Bank();
	
};

Bank::Bank()
{
	Account acc;
	ifstream ifs("Bank.txt");
	if (!ifs.is_open())
		return;
	while (!ifs.eof())
	{
		ifs >> acc;
		int accountNum = acc.getAccountNum();
		int count = acc.getCount();
		if (accountNum > count)
			acc.setCount(accountNum);
		accounts.insert(pair<int, Account>(acc.getAccountNum(), acc));
		
	}
	ifs.close();
}

void Bank::withdrawal(int accountNum, int balance)
{
	map<int, Account>::iterator itr;
	itr = accounts.find(accountNum);
	int newBalance = (itr->second).getBalance() - balance;
	(itr->second).setBalance(newBalance);
}

void Bank::createAccount(string firstName, string lastName, int balance)
{
	Account acc(firstName, lastName, balance);
	ofstream ofs("Bank.txt", ios::app);
	ofs << acc;
	accounts.insert(pair<int, Account>(acc.getAccountNum(), acc));
	ofs.close();
}

void Bank::showAllAccounts()
{
	map<int, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		cout << "Account " << itr->first;
		cout << itr->second;
	}
}

void Bank::deposit(int accountNum, int balance)
{
	map<int, Account>::iterator itr;
	itr = accounts.find(accountNum);
	int newBalance = (itr->second).getBalance() + balance;
	(itr->second).setBalance(newBalance);
}

map<int, Account> Bank::getAccounts() { return accounts; }

void Bank::closeAccount(int acountNum) {
	accounts.erase(acountNum);
}

Account Bank::balanceEnquiry(int accountNum)
{
	map<int, Account>::iterator itr;
	itr = accounts.find(accountNum);
	return itr->second;
}

Bank::~Bank()
{
	ofstream ofs("Bank.txt",ios::trunc);
	map<int, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
		ofs << itr->second;
	ofs.close();
}

int main()
{
	Account acc;
	Bank bank;
	cout << "***Banking System***\n" << endl;
	int choice;
	string firstName, lastName;
	int chooseAcc;
	int balance;	
	while (true)
	{
		cout << "	Select one option below" << endl;
		cout << "	1. Open an Account" << endl;
		cout << "	2. Balance Enquiry" << endl;
		cout << "	3. Deposit" << endl;
		cout << "	4. Withdrawal" << endl;
		cout << "	5. Close an Account" << endl;
		cout << "	6. Show All Accounts" << endl;
		cout << "	7. Quit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case OPEN_ACCOUNT:
			cout << "Enter First Name: ";
			cin >> firstName;
			cout << "Enter Last Name: ";
			cin >> lastName;
			cout << "Enter initial balance: ";
			cin >> balance;
			bank.createAccount(firstName, lastName, balance);
			cout << "Congratsulation Account is created" << endl;
			break;
		case BALANCE_ENQUIRY:
			cout << "Enter account number: ";

			cin >> chooseAcc;
			acc = bank.balanceEnquiry(chooseAcc);
			cout << acc;
			break;
		case DEPOSIT:
			cout << "Enter account number: ";
			cin >> chooseAcc;
			cout << "Enter Balance: ";
			cin >> balance;
			bank.deposit(chooseAcc, balance);
			cout << "Amount is Deposited" << endl;
			acc = bank.balanceEnquiry(chooseAcc);
			cout << acc;
		case WITHDRAWAL:
			cout << "Enter account number: ";
			cin >> chooseAcc;
			cout << "Enter Balance: ";
			cin >> balance;
			bank.deposit(chooseAcc, balance);
			cout << "Amount is Deposited" << endl;
			acc = bank.balanceEnquiry(chooseAcc);
			cout << acc;
			break;
		case CLOSE_ACCOUNT:
			cout << "Enter account number: ";
			cin >> chooseAcc;
			bank.closeAccount(chooseAcc);
			break;
		case SHOW_ALL_ACCOUNTS:
			bank.showAllAccounts();
			break;
		case QUIT:
			cout << "Cya" << endl;
			return 0;
		default:
			cout << "Wrong decision inserted" << endl;
			break;
		}
	}
	return 0;
}
