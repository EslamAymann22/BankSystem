#include<bits/stdc++.h>

using namespace std;

class User {
public:
	string username;
	string password;
	string gmail;
};
class Date {
public:
	int day;
	int month;
	int year;
};
class Operation {
public:
	string From;
	string To;
	int AmountOfMomy;
};

class Card {
public:
	string CardName;
	string CardNum;
	string CardPIN;
	Date ExpDate;
	string CVV;
	int ZipCode;
	string PhoneNumber;
	double Mony;
	string BankName;

	virtual void SendMony(Card*, double) = 0;
	virtual bool CanSend(double) = 0;
	void operator += (double amount) {
		this->Mony += amount;
	}
	void operator -= (double amount) {
		this->Mony -= amount;
	}
	void Changepassword(string NewPassword) {
		this->CardPIN = NewPassword;
	}
	Card() {
		ZipCode = 0;
		Mony = 0;
	}
};

class VisaCard : public Card {
public:
	void SendMony(Card* receiver, double amount) {
		*this -= amount;
		*receiver += amount;
	}
	bool CanSend(double c) {
		return (c > 0 and c <= this->Mony);
	}

};

class MasterCard : public Card {
public:
	double tax = 0;
	void SendMony(Card* receiver, double amount) {
		*this -= amount + amount * tax;
		*receiver += amount;
	}
	bool CanSend(double c) {
		return (c > 0 and (c + c * tax) <= this->Mony);
	}
};

class TypeCard {
public:
	bool Visa;
	int ID;
	TypeCard(bool Visa = 0, int ID = 0) :Visa(Visa), ID(ID) {}
};
class Account {
public:
	User user;
	TypeCard DefultCard;
	string IPA_Num;
	int NumberOfVisaCardsInAccount;
	vector<int>MyVisaCards;
	int NumberOfMasterCardsInAccount;
	vector<int>MyMasterCards;
	int NumberOfTransInAccount;
	vector<int>MyTrans;
	Account() {
		NumberOfVisaCardsInAccount = 0;
		NumberOfMasterCardsInAccount = 0;
		NumberOfTransInAccount = 0;
	}
};

vector<Account>accounts;
vector<VisaCard>visacards;
vector<MasterCard>mastercards;
vector<Operation>operations;

bool FoundFile(ifstream& fin) {
	return fin.good();
}
bool FoundFile(ofstream& fin) {
	return fin.good();
}

void DownloadData() {
	ifstream fin("Accounts.txt");
	if (!FoundFile(fin)) {
		cout << "Can't open " << "Accounts.txt" << " File \n\n";
		fin.close();
	}
	while (!fin.fail()) {
		accounts.push_back(Account());
		fin >> accounts.back().user.username;
		fin >> accounts.back().user.password;
		fin >> accounts.back().user.gmail;
		fin >> accounts.back().DefultCard.Visa;
		fin >> accounts.back().DefultCard.ID;
		fin >> accounts.back().IPA_Num;
		fin >> accounts.back().NumberOfVisaCardsInAccount;
		accounts.back().MyVisaCards.resize(accounts.back().NumberOfVisaCardsInAccount);
		for (int i = 0; i < accounts.back().NumberOfVisaCardsInAccount; i++) {
			fin >> accounts.back().MyVisaCards[i];
		}
		fin >> accounts.back().NumberOfMasterCardsInAccount;
		accounts.back().MyMasterCards.resize(accounts.back().NumberOfMasterCardsInAccount);
		for (int i = 0; i < accounts.back().NumberOfMasterCardsInAccount; i++) {
			fin >> accounts.back().MyMasterCards[i];
		}
		fin >> accounts.back().NumberOfTransInAccount;
		accounts.back().MyTrans.resize(accounts.back().NumberOfTransInAccount);
		for (int i = 0; i < accounts.back().NumberOfTransInAccount; i++) {
			fin >> accounts.back().MyTrans[i];
		}
		if (fin.fail())accounts.pop_back();
	}
	fin.close();
	fin.open("VisaCards.txt");
	if (!FoundFile(fin)) {
		cout << "Can't open " << "VisaCards.txt" << " File \n\n";
		fin.close();
	}
	while (!fin.fail()) {
		visacards.push_back(VisaCard());
		fin >> visacards.back().CardName;
		fin >> visacards.back().CardNum;
		fin >> visacards.back().CardPIN;
		fin >> visacards.back().ExpDate.day;
		fin >> visacards.back().ExpDate.month;
		fin >> visacards.back().ExpDate.year;
		fin >> visacards.back().CVV;
		fin >> visacards.back().ZipCode;
		fin >> visacards.back().PhoneNumber;
		fin >> visacards.back().Mony;
		fin >> visacards.back().BankName;
		if (fin.fail())visacards.pop_back();

	}
	fin.close();
	fin.open("MasterCards.txt");
	if (!FoundFile(fin)) {
		cout << "Can't open " << "MasterCards.txt" << " File \n\n";
		fin.close();
	}
	while (!fin.fail()) {
		mastercards.push_back(MasterCard());
		fin >> mastercards.back().CardName;
		fin >> mastercards.back().CardNum;
		fin >> mastercards.back().CardPIN;
		fin >> mastercards.back().ExpDate.day;
		fin >> mastercards.back().ExpDate.month;
		fin >> mastercards.back().ExpDate.year;
		fin >> mastercards.back().CVV;
		fin >> mastercards.back().ZipCode;
		fin >> mastercards.back().PhoneNumber;
		fin >> mastercards.back().Mony;
		fin >> mastercards.back().BankName;
		fin >> mastercards.back().tax;
		if (fin.fail())mastercards.pop_back();

	}
	fin.close();
	fin.open("Operations.txt");
	if (!FoundFile(fin)) {
		cout << "Can't open " << "Operations.txt" << " File \n\n";
		fin.close();
	}
	while (!fin.fail()) {
		operations.push_back(Operation());
		fin >> operations.back().From;
		fin >> operations.back().To;
		fin >> operations.back().AmountOfMomy;
		if (fin.fail())operations.pop_back();
	}
	fin.close();
}

void UploadData() {
	ofstream fout("Accounts.txt");
	if (!FoundFile(fout)) {
		cout << "Can't open " << "Accounts.txt" << " File \n\n";
		fout.close();
	}
	for (auto it : accounts) {
		fout << it.user.username << '\n';
		fout << it.user.password << '\n';
		fout << it.user.gmail << '\n';
		fout << it.DefultCard.Visa << ' ';
		fout << it.DefultCard.ID << '\n';
		fout << it.IPA_Num << '\n';
		fout << it.MyVisaCards.size() << '\n';
		for (auto it2 : it.MyVisaCards) {
			fout << it2 << ' ';
		}
		fout << '\n';
		fout << it.MyMasterCards.size() << '\n';
		for (auto it2 : it.MyMasterCards) {
			fout << it2 << ' ';
		}
		fout << '\n';
		fout << it.MyTrans.size() << '\n';
		for (auto it2 : it.MyTrans) {
			fout << it2 << ' ';
		}
		fout << '\n';
	}
	fout.close();
	fout.open("VisaCards.txt");
	if (!FoundFile(fout)) {
		cout << "Can't open " << "VisaCards.txt" << " File \n\n";
		fout.close();
	}
	for (auto it : visacards) {
		fout << it.CardName << '\n';
		fout << it.CardNum << '\n';
		fout << it.CardPIN << '\n';
		fout << it.ExpDate.day << '\n';
		fout << it.ExpDate.month << '\n';
		fout << it.ExpDate.year << '\n';
		fout << it.CVV << '\n';
		fout << it.ZipCode << '\n';
		fout << it.PhoneNumber << '\n';
		fout << it.Mony << '\n';
		fout << it.BankName << '\n';
	}
	fout.close();
	fout.open("MasterCards.txt");
	if (!FoundFile(fout)) {
		cout << "Can't open " << "MasterCards.txt" << " File \n\n";
		fout.close();
	}
	for (auto it : mastercards) {
		fout << it.CardName << '\n';
		fout << it.CardNum << '\n';
		fout << it.CardPIN << '\n';
		fout << it.ExpDate.day << '\n';
		fout << it.ExpDate.month << '\n';
		fout << it.ExpDate.year << '\n';
		fout << it.CVV << '\n';
		fout << it.ZipCode << '\n';
		fout << it.PhoneNumber << '\n';
		fout << it.Mony << '\n';
		fout << it.BankName << '\n';
		fout << it.tax << '\n';
	}
	fout.close();
	fout.open("Operations.txt");
	if (!FoundFile(fout)) {
		cout << "Can't open " << "Operations.txt" << " File \n\n";
		fout.close();
	}
	for (auto it : operations) {
		fout << it.From << ' ' << it.To << ' ' << it.AmountOfMomy << '\n';
	}
	fout.close();
}

class AccountServes {


	bool ValidGmail(string Gmail) {

		bool dot = 0, att = 0;
		for (int i = 0; i < Gmail.size(); i++) {
			char it = Gmail[i];
			if (it == '.') {
				if (dot || !att || i == 0 || Gmail[i - 1] == '@' || i == Gmail.size() - 1)return 0;
				dot = 1;
			}
			if (it == '@') {
				if (att || i == 0)return 0;
				att = 1;
			}
		}
		return dot and att;
	}
	bool UniqeGmail(string gmail) {
		for (auto it : accounts) {
			if (it.user.gmail == gmail)return 0;
		}
		return 1;
	}
	string GetGmail() {
		string Gmail;
		cin >> Gmail;
		while (!UniqeGmail(Gmail) || !ValidGmail(Gmail)) {
			cout << "Enter another Gmail : ";
			cin >> Gmail;
		}
		return Gmail;
	}
	bool ValidUser(string user) {
		// a A 213 _ . 
		for (auto it : user) {
			int cnt = 0;
			cnt += (it >= 'a' and it <= 'z');
			cnt += (it >= 'A' and it <= 'Z');
			cnt += (it >= '0' and it <= '9');
			cnt += it == '.';
			cnt += it == '_';
			if (cnt == 0)return 0;
		}
		return 1;
	}
	bool UniqeUser(string user) {
		for (auto it : accounts) {
			if (it.user.username == user)return 0;
		}
		return 1;
	}
	int chickAccount(string username, string pass) {
		int ret = 0;
		for (auto it : accounts) {
			if (it.user.username == username) {
				if (it.user.password == pass)return ret;
				return -1;
			}
			ret++;
		}
		return -1;
	}
	string GetUser() {
		string user;
		cin >> user;
		while (!UniqeUser(user) || !ValidUser(user)) {
			cout << "Enter another account : "; cin >> user;
		}
		return user;
	}
	string GetCard(int cnt) {
		string s;
		cin >> s;
		while (!ValidInput(s, cnt)) {
			cout << "Enter another number : "; cin >> s;
		}
		return s;
	}

	bool ValidInput(string cardnum, int cnt) {
		for (auto it : cardnum) {
			if (it >= '0' and it <= '9')continue;
			return 0;
		}
		return (cardnum.size() == cnt);
	}
	int ChickVisaCard(VisaCard& card) {
		int ret = 0;
		for (VisaCard it : visacards) {
			if (it.CardNum == card.CardNum and it.BankName == card.BankName) {
				if (it.CardPIN == card.CardPIN) {
					if (it.CVV == card.CVV) {
						card = it;
						return ret;
					}
				}
				return -1;
			}
			ret++;
		}
		return -1;
	}
	int ChickMasterCard(MasterCard& card) {
		int ret = 0;
		for (MasterCard it : mastercards) {
			if (it.CardNum == card.CardNum and it.BankName == card.BankName) {
				if (it.CardPIN == card.CardPIN) {
					if (it.CVV == card.CVV) {
						card = it;
						return ret;
					}

				}
				return -1;
			}
			ret++;
		}
		return -1;
	}
	TypeCard ChooseDefultCard(Account& account) {
		int id = 1;
		for (auto it : account.MyVisaCards) {
			cout << id++ << ' ' << visacards[it].CardNum << '\n';
		}
		for (auto it : account.MyMasterCards) {
			cout << id++ << ' ' << mastercards[it].CardNum << '\n';
		}
		int ch = -1;
		while (ch <= 0) {
			cout << "Enter number in range 1 - " << id - 1 << " : "; cin >> ch;
			if (ch >= id)ch = 0;
		}
		ch--;
		TypeCard ret(0, -1);
		if (ch < account.MyVisaCards.size()) {
			ret.Visa = 1;
			ret.ID = account.MyVisaCards[ch];;
			return ret;
		}
		else {
			ch -= account.MyVisaCards.size();
			ret.Visa = 0;
			ret.ID = account.MyMasterCards[ch];
			return ret;
		}
	}

public:
	int LogIn() {
		string username, password;
		cout << "Enter username : "; cin >> username; cout << '\n';
		cout << "Enter password : "; cin >> password; cout << '\n';
		return chickAccount(username, password);
	}
	int SignUp() {
		accounts.push_back(Account());
		cout << "Enter Username : "; accounts.back().user.username = GetUser();
		cout << "Enter Gmail : "; accounts.back().user.gmail = GetGmail();
		cout << "Enter password : "; cin >> accounts.back().user.password;
		int op = -1;
		while (op != 1 and op != 2) {
			cout << "1 : Visa Card\n";
			cout << "2 : Master Card\n";
			cout << "Enter : "; cin >> op;
		}
		if (op == 1) {
			AddVisaCard(accounts.back());
			accounts.back().DefultCard.Visa = 1;
			accounts.back().DefultCard.ID = accounts.back().MyVisaCards.back();
		}
		else {
			AddMasterCard(accounts.back());
			accounts.back().DefultCard.Visa = 0;
			accounts.back().DefultCard.ID = accounts.back().MyMasterCards.back();

		}
		accounts.back().IPA_Num = to_string(accounts.size());
		while (accounts.back().IPA_Num.size() < 6)
			accounts.back().IPA_Num = "0" + accounts.back().IPA_Num;

		cout << "Yout IPA number is : " << accounts.back().IPA_Num << '\n';
		return accounts.size() - 1;
	}
	void ChangeDefultCard(Account& account) {
		account.DefultCard = ChooseDefultCard(account);
	}
	void AddVisaCard(Account& account) {
		VisaCard tmp;
		int ok = 0;
		int idcs = -1;
		do {
			if (ok)cout << "Not founded!!\n";
			cout << "Enter Card number : "; tmp.CardNum = GetCard(16);
			cout << "Enter Card PIN    : "; tmp.CardPIN = GetCard(04);
			cout << "Enter Card CVV    : "; tmp.CVV = GetCard(03);
			cout << "Enter Bank name   : "; cin >> tmp.BankName;
			ok = 1;
			idcs = ChickVisaCard(tmp);
		} while (idcs < 0);
		for (auto it : account.MyVisaCards) {
			if (idcs == it)return cout << "Card already founnded\n", void();
		}
		account.MyVisaCards.push_back(idcs);
		account.NumberOfVisaCardsInAccount++;
	}
	void AddMasterCard(Account& account) {
		MasterCard tmp;
		int ok = 0;
		int idcs = -1;
		do {
			if (ok)cout << "Not founded!!\n";
			cout << "Enter Card number : "; tmp.CardNum = GetCard(16);
			cout << "Enter Card PIN    : "; tmp.CardPIN = GetCard(04);
			cout << "Enter Card CVV    : "; tmp.CVV = GetCard(03);
			cout << "Enter Bank name   : "; cin >> tmp.BankName;
			ok = 1;
			idcs = ChickMasterCard(tmp);
		} while (idcs < 0);
		for (auto it : account.MyMasterCards) {
			if (idcs == it)return cout << "Card already founnded\n", void();
		}
		account.MyMasterCards.push_back(idcs);
		account.NumberOfMasterCardsInAccount++;
	}
};

class CardServes {
	Card* ChooseCard(Account& account) {
		int ch = 0;
		while (ch < 1) {
			int id = 1;
			for (auto it : account.MyVisaCards) {
				cout << id++ << ' ' << visacards[it].CardNum << '\n';
			}
			for (auto it : account.MyMasterCards) {
				cout << id++ << ' ' << mastercards[it].CardNum << '\n';
			}

			cout << "Enter id card : "; cin >> ch;
			if (ch >= id)ch = -1;
			if (id == 1) {
				ch = -5; break;
			}
		}
		ch--;
		if (ch < account.MyVisaCards.size() and ch>-1) {
			return &visacards[account.MyVisaCards[ch]];
		}
		else if (ch > -1) {
			ch -= account.MyVisaCards.size();
			return &mastercards[account.MyMasterCards[ch]];
		}
		cout << "You havn't any card in your account \n";
		return &visacards[0];
	}
	Card* ChooseReceiverCard() {
		string card;
		while (1) {
			cout << "Enter Number of card or IPA Account";
			cin >> card;
			if (card.size() == 6) {
				for (Account& it : accounts) {
					if (it.IPA_Num == card) {
						if (it.DefultCard.Visa) {
							return &visacards[it.DefultCard.ID];
						}
						else {
							return &mastercards[it.DefultCard.ID];
						}
					}
				}
			}
			else if (card.size() == 16) {
				string bankname;
				cout << "Enter Bank name"; cin >> bankname;
				for (VisaCard& it : visacards) {
					if (it.CardNum == card and it.BankName == bankname)return &it;
				}
				for (MasterCard& it : mastercards) {
					if (it.CardNum == card and it.BankName == bankname)return &it;
				}
			}
		}
	}
	int AddTrans(string from, string to, double amount) {
		operations.push_back(Operation());
		operations.back().From = from;
		operations.back().To = to;
		operations.back().AmountOfMomy = amount;
		return operations.size() - 1;
	}
	int getIdReceiver(Card* card) {
		int ret = -1;
		for (auto it : accounts) {
			ret++;
			for (int it2 : it.MyVisaCards) {
				if (visacards[it2].CardNum == card->CardNum)return ret;
			}
			for (int it2 : it.MyMasterCards) {
				if (mastercards[it2].CardNum == card->CardNum)return ret;
			}
		}
	}
	double GetAmount(Card* senderCard) {
		double AmountOfMony = 0, ok = 0;
		while (!senderCard->CanSend(AmountOfMony)) {
			if (ok)cout << "Unvalid number\n";
			cout << "Your mony = " << senderCard->Mony << '\n';
			cout << "Enter amount of mony want send : "; cin >> AmountOfMony;
			ok = 1;
		}
		return AmountOfMony;
	}
	bool ValidInput(string cardnum, int cnt) {
		for (auto it : cardnum) {
			if (it >= '0' and it <= '9')continue;
			return 0;
		}
		return (cardnum.size() == cnt);
	}
public:

	void SendMony(Account& account) {
		Card* receiverCard;
		Card* senderCard;
		senderCard = ChooseCard(account);
		receiverCard = ChooseReceiverCard();
		int idReceiver = getIdReceiver(receiverCard);
		if (senderCard == receiverCard)return cout << "\n\nyou cant send mony to same card!!\n", void();
		double amount = GetAmount(senderCard);
		senderCard->SendMony(receiverCard, amount);
		account.MyTrans.push_back(AddTrans(senderCard->CardNum, receiverCard->CardNum, amount));
		account.NumberOfTransInAccount = account.MyTrans.size();
		accounts[idReceiver].MyTrans.push_back(operations.size() - 1);
		accounts[idReceiver].NumberOfTransInAccount = accounts[idReceiver].MyTrans.size();
		cout << "\n\nSuccesful !!\n\n";
	}
	void ChangPassword(Account& account) {
		Card* card = ChooseCard(account);
		string pin = "";
		while (pin.empty()) {
			cout << "Enter old card PIN : "; cin >> pin;
			if (pin == card->CardPIN)break;
			pin = "";
		}

		pin = "";
		while (pin.empty()) {
			cout << "Enter new pin : "; cin >> pin;
			if (ValidInput(pin, 4))break;
			pin = "";
		}
		card->CardPIN = pin;

	}
	void ShowMyTrans(Account& account) {
		for (auto it : account.MyTrans) {
			cout << "From : " << operations[it].From << "  To  " << operations[it].To << " Send " << operations[it].AmountOfMomy << " $\n";
		}
	}
	void ShowMyTrans(Account& account,Card* card) {
		for (auto it : account.MyTrans) {
			if (operations[it].From != card->CardNum and operations[it].To != card->CardNum)continue;
			cout << "From : " << operations[it].From << "  To  " << operations[it].To << " Send " << operations[it].AmountOfMomy << " $\n";
		}
	}
	void ShowCardData(Account& account) {
		Card* card = ChooseCard(account);
		cout << "Card name : " << card->CardName << '\n';
		cout << "Bank Name of card : " << card->BankName << '\n';
		cout << "PIN Card : " << card->CardPIN << '\n';
		cout << "Card number : " << card->CardNum << '\n';
		cout << "Card CVV : " << card->CVV << '\n';
		cout << "Card Expired Date : " << card->ExpDate.day << '/' << card->ExpDate.month << '/' << card->ExpDate.year << '\n';
		cout << "Card many : " << card->Mony << " $" << '\n';
		cout << "ZIP code of card : " << card->ZipCode << '\n';
		cout << "phone of card : " << card->PhoneNumber << '\n';
		cout << "\n\n\n\nYour trans \n\n\n";
		ShowMyTrans(account,card);
	}
	void RemoveCard(Account& account) {
		if (account.MyMasterCards.size() + account.MyVisaCards.size() < 2) {
			cout << "\n\nYou must have at least 2 account2\n\n";
			return;
		}
		Card* card = ChooseCard(account);
		for (int i = 0; i < account.MyMasterCards.size(); i++) {
			if (mastercards[account.MyMasterCards[i]].CardNum == card->CardNum) {


				if (account.MyMasterCards[i] == account.DefultCard.ID and account.DefultCard.Visa == 0) {
					if (account.MyVisaCards.size() > 0) {
						account.DefultCard = TypeCard(1, account.MyVisaCards.front());
					}
					else if (account.MyMasterCards.size() > 1) {
						account.DefultCard = TypeCard(0, account.MyMasterCards.front());
					}
				}

				account.MyMasterCards.erase(account.MyMasterCards.begin() + i, account.MyMasterCards.begin() + i + 1);
				account.NumberOfMasterCardsInAccount--;

				break;
			}
		}
		for (int i = 0; i < account.MyVisaCards.size(); i++) {
			if (visacards[account.MyVisaCards[i]].CardNum == card->CardNum) {


				if (account.MyVisaCards[i] == account.DefultCard.ID and account.DefultCard.Visa == 1) {

					if (account.MyVisaCards.size() > 1) {
						account.DefultCard = TypeCard(1, account.MyVisaCards.front());
					}
					else if (account.MyMasterCards.size() > 0) {
						account.DefultCard = TypeCard(0, account.MyMasterCards.front());
					}

				}

				account.MyVisaCards.erase(account.MyVisaCards.begin() + i, account.MyVisaCards.begin() + i + 1);
				account.NumberOfVisaCardsInAccount--;
				break;
			}
		}
	}

};

class add_data {

	bool UniqeNum(string s) {
		for (auto it : visacards)if (s == it.CardNum)return 0;
		for (auto it : mastercards)if (s == it.CardNum)return 0;
		for (auto it : s)if (it < '0' || it>'9')return 0;
		return s.size() == 16;
	}
	bool validPIN(string s, int n) {
		for (auto it : s)if (!(it >= '0' and it <= '9'))return 0;
		return s.size() == n;
	}
	string GetNum() {
		int ok = -1;
		string s;
		while (ok < 0) {
			ok = 9;
			cout << "Enter  : "; cin >> s;
			if (!UniqeNum(s))ok = -1;
		}
		return s;
	}
	string GetJustNum(int n) {
		int ok = -1;
		string s;
		while (ok < 0) {
			ok = 9;
			cout << "Enter  : "; cin >> s;
			if (!validPIN(s, n))ok = -1;
		}
		return s;
	}
public:
	add_data() {
		DownloadData();
	}
	void add() {
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
	~add_data() {
		UploadData();;
	}
};

class System {
public:
	System() {
		DownloadData();
	}
	AccountServes account_serves;
	CardServes card_serves;
	~System() {
		UploadData();
	}
};

void InstaPaySystem() {
	System manger;
	int cur_id = -1;
	while (1) {
		while (cur_id < 0) {
			cout << "LogIn  : 1\n";
			cout << "SignUp : 2\n";
			cout << "Exit   : 3\n";
			int op;
			cout << "Enter : "; cin >> op;
			if (op == 1) {
				cur_id = manger.account_serves.LogIn();
				if (cur_id == -1) {
					cout << "Inccorect password or username\n";
				}
			}
			else if (op == 2) {
				cur_id = manger.account_serves.SignUp();
			}
			else if (op == 3) {
				return;
			}
			else cout << "ERROR!!\n";
		}
		cout << " Your ID = " << cur_id << '\n' << '\n';//////////////////////////////////
		cout << "1 : Send mony \n";
		cout << "2 : Change defult card in account \n";
		cout << "3 : Add visa card \n";
		cout << "4 : Add master card \n";
		cout << "5 : Remove card \n";
		cout << "6 : Show cards data \n";
		cout << "7 : Show my trans in card\n";
		cout << "8 : Change Card PIN\n";
		cout << "9 : Log Out\n";
		int op;
		cout << "Enter number in range 1 - 9 "; cin >> op;
		if (op == 1) {
			manger.card_serves.SendMony(accounts[cur_id]);
		}
		else if (op == 2) {
			manger.account_serves.ChangeDefultCard(accounts[cur_id]);
		}
		else if (op == 3) {
			manger.account_serves.AddVisaCard(accounts[cur_id]);
		}
		else if (op == 4) {
			manger.account_serves.AddMasterCard(accounts[cur_id]);
		}
		else if (op == 5) {
			manger.card_serves.RemoveCard(accounts[cur_id]);
		}
		else if (op == 6) {
			manger.card_serves.ShowCardData(accounts[cur_id]);
		}
		else if (op == 7) {
			manger.card_serves.ShowMyTrans(accounts[cur_id]);
		}
		else if (op == 8) {
			manger.card_serves.ChangPassword(accounts[cur_id]);
		}
		else if (op == 9) {
			cur_id = -1;
		}
		else cout << "ERROR!!\n";
	}
}


int main() {

	//add_data().add();

	InstaPaySystem();
}