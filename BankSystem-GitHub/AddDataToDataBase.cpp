#include "AddDataToDataBase.h"

bool AddDataToDataBase::UniqeNum(string s) {
	for (auto it : visacards)if (s == it.CardNum)return 0;
	for (auto it : mastercards)if (s == it.CardNum)return 0;
	for (auto it : s)if (it < '0' || it>'9')return 0;
	return s.size() == 16;
}

bool AddDataToDataBase::validPIN(string s, int n) {
	for (auto it : s)if (!(it >= '0' and it <= '9'))return 0;
	return s.size() == n;
}

string AddDataToDataBase::GetNum() {
	int ok = -1;
	string s;
	while (ok < 0) {
		ok = 9;
		cout << "Enter  : "; cin >> s;
		if (!UniqeNum(s))ok = -1;
	}
	return s;
}

string AddDataToDataBase::GetJustNum(int n) {
	int ok = -1;
	string s;
	while (ok < 0) {
		ok = 9;
		cout << "Enter  : "; cin >> s;
		if (!validPIN(s, n))ok = -1;
	}
	return s;
}

void AddDataToDataBase::add(vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards, vector<Operation>& operations)

{
	int ok = 1;
	while (ok > 0) {
		cout << "visa : 1 master : 2  : "; cin >> ok;
		if (ok == 1) {
			visacards.push_back(VisaCard());
			cout << "Enter card name : "; cin >> visacards.back().CardName;
			cout << "Enter card num : "; visacards.back().CardNum = GetNum();
			cout << "Enter card PIN : "; visacards.back().CardPIN = GetJustNum(4);
			cout << "Enter card ExDate d : "; cin >> visacards.back().ExpDate.day;
			cout << "Enter card ExDate m : "; cin >> visacards.back().ExpDate.month;
			cout << "Enter card ExDate y : "; cin >> visacards.back().ExpDate.year;
			cout << "Enter card CVV : "; visacards.back().CVV = GetJustNum(3);
			cout << "Enter card ZipCode : "; cin >> visacards.back().ZipCode;
			cout << "Enter card phone : "; visacards.back().PhoneNumber = GetJustNum(11);
			cout << "Enter card mony : "; cin >> visacards.back().Mony;
			cout << "Enter bank name : "; cin >> visacards.back().BankName;
		}
		else {
			mastercards.push_back(MasterCard());
			cout << "Enter card name : "; cin >> mastercards.back().CardName;
			cout << "Enter card num : "; mastercards.back().CardNum = GetNum();
			cout << "Enter card PIN : "; mastercards.back().CardPIN = GetJustNum(4);
			cout << "Enter card ExDate d : "; cin >> mastercards.back().ExpDate.day;
			cout << "Enter card ExDate m : "; cin >> mastercards.back().ExpDate.month;
			cout << "Enter card ExDate y : "; cin >> mastercards.back().ExpDate.year;
			cout << "Enter card CVV : "; mastercards.back().CVV = GetJustNum(3);
			cout << "Enter card ZipCode : "; cin >> mastercards.back().ZipCode;
			cout << "Enter card phone : "; mastercards.back().PhoneNumber = GetJustNum(11);
			cout << "Enter card mony : "; cin >> mastercards.back().Mony;
			cout << "Enter bank name : "; cin >> mastercards.back().BankName;
			cout << "Enter CArd tax: "; cin >> mastercards.back().tax;
		}

		cout << "Add another test ? 1 : -1"; cin >> ok;
	}
}