#include "AccountServes.h"

bool AccountServes::ValidGmail(string Gmail) {

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

bool AccountServes::UniqeGmail(string gmail, vector<Account>& accounts) {
	for (auto it : accounts) {
		if (it.gmail == gmail)return 0;
	}
	return 1;
}

string AccountServes::GetGmail(vector<Account>& accounts) {
	string Gmail;
	cin >> Gmail;
	while (!UniqeGmail(Gmail, accounts) || !ValidGmail(Gmail)) {
		cout << "Enter another Gmail : ";
		cin >> Gmail;
	}
	return Gmail;
}

bool AccountServes::ValidUser(string user) {
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

bool AccountServes::UniqeUser(string user, vector<Account>& accounts) {
	for (auto it : accounts) {
		if (it.username == user)return 0;
	}
	return 1;
}

int AccountServes::chickAccount(string username, string pass, vector<Account>& accounts) {
	int ret = 0;
	for (auto it : accounts) {
		if (it.username == username) {
			if (it.password == pass)return ret;
			return -1;
		}
		ret++;
	}
	return -1;
}

string AccountServes::GetUser(vector<Account>& accounts) {
	string user;
	cin >> user;
	while (!UniqeUser(user, accounts) || !ValidUser(user)) {
		cout << "Enter another account : "; cin >> user;
	}
	return user;
}

string AccountServes::GetCard(int cnt) {
	string s;
	cin >> s;
	while (!ValidInput(s, cnt)) {
		cout << "Enter another number : "; cin >> s;
	}
	return s;
}

bool AccountServes::ValidInput(string cardnum, int cnt) {
	for (auto it : cardnum) {
		if (it >= '0' and it <= '9')continue;
		return 0;
	}
	return (cardnum.size() == cnt);
}

int AccountServes::ChickVisaCard(VisaCard& card, vector<VisaCard>& visacards) {
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

int AccountServes::ChickMasterCard(MasterCard& card, vector<MasterCard>& mastercards) {
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

TypeCard AccountServes::ChooseDefultCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
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
		ret.IsVisa = 1;
		ret.ID = account.MyVisaCards[ch];;
		return ret;
	}
	else {
		ch -= account.MyVisaCards.size();
		ret.IsVisa = 0;
		ret.ID = account.MyMasterCards[ch];
		return ret;
	}
}

int AccountServes::LogIn(vector<Account>& accounts)
{
	string username, password;
	cout << "Enter username : "; cin >> username; cout << '\n';
	cout << "Enter password : "; cin >> password; cout << '\n';
	return chickAccount(username, password, accounts);
}

int AccountServes::SignUp(vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	accounts.push_back(Account());
	cout << "Enter Username : "; accounts.back().username = GetUser(accounts);
	cout << "Enter Gmail : "; accounts.back().gmail = GetGmail(accounts);
	cout << "Enter password : "; cin >> accounts.back().password;
	int op = -1;
	while (op != 1 and op != 2) {
		cout << "1 : Visa Card\n";
		cout << "2 : Master Card\n";
		cout << "Enter : "; cin >> op;
	}
	if (op == 1) {
		AddVisaCard(accounts.back(), visacards);
		accounts.back().DefultCard.IsVisa = 1;
		accounts.back().DefultCard.ID = accounts.back().MyVisaCards.back();
	}
	else {
		AddMasterCard(accounts.back(), mastercards);
		accounts.back().DefultCard.IsVisa = 0;
		accounts.back().DefultCard.ID = accounts.back().MyMasterCards.back();

	}
	accounts.back().IPA_Num = to_string(accounts.size());
	while (accounts.back().IPA_Num.size() < 6)
		accounts.back().IPA_Num = "0" + accounts.back().IPA_Num;

	cout << "Yout IPA number is : " << accounts.back().IPA_Num << '\n';
	return accounts.size() - 1;
}

void AccountServes::ChangeDefultCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	account.DefultCard = ChooseDefultCard(account, visacards, mastercards);
}

void AccountServes::AddVisaCard(Account& account, vector<VisaCard>& visacards) {
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
		idcs = ChickVisaCard(tmp, visacards);
	} while (idcs < 0);
	for (auto it : account.MyVisaCards) {
		if (idcs == it)return cout << "Card already founnded\n", void();
	}
	account.MyVisaCards.push_back(idcs);
	account.NumberOfVisaCardsInAccount++;
}

void AccountServes::AddMasterCard(Account& account, vector<MasterCard>& mastercards) {
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
		idcs = ChickMasterCard(tmp, mastercards);
	} while (idcs < 0);
	for (auto it : account.MyMasterCards) {
		if (idcs == it)return cout << "Card already founnded\n", void();
	}
	account.MyMasterCards.push_back(idcs);
	account.NumberOfMasterCardsInAccount++;
}