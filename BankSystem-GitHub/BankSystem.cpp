#include "BankSystem.h"

bool BankSystem::FoundFile(ifstream& fin) {
	return fin.good();
}

bool BankSystem::FoundFile(ofstream& fin) {
	return fin.good();
}

void BankSystem::DownloadData() {
	ifstream fin("Accounts.txt");
	if (!FoundFile(fin)) {
		cout << "Can't open " << "Accounts.txt" << " File \n\n";
		fin.close();
	}
	while (!fin.fail()) {
		accounts.push_back(Account());
		fin >> accounts.back().username;
		fin >> accounts.back().password;
		fin >> accounts.back().gmail;
		fin >> accounts.back().DefultCard.IsVisa;
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

void BankSystem::UploadData() {
	ofstream fout("Accounts.txt");
	if (!FoundFile(fout)) {
		cout << "Can't open " << "Accounts.txt" << " File \n\n";
		fout.close();
	}
	for (auto it : accounts) {
		fout << it.username << '\n';
		fout << it.password << '\n';
		fout << it.gmail << '\n';
		fout << it.DefultCard.IsVisa << ' ';
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

BankSystem::BankSystem() {
	DownloadData();
	cout << "Are you want add some data to data base ? \n";
	string s;
	cout << "Enter Yes / No : "; cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') {
		AddData.add(accounts, visacards, mastercards, operations);
	}
	//RunSystem();
}

void BankSystem::Run() {
	int cur_id = -1;
	while (true) {
		while (cur_id < 0) {
			cout << "LogIn  : 1\n";
			cout << "SignUp : 2\n";
			cout << "Exit   : 3\n";
			int op;
			cout << "Enter : "; cin >> op;
			if (op == 1) {
				cur_id = AccSer.LogIn(accounts);
				if (cur_id == -1) {
					cout << "Inccorect password or username\n";
				}
			}
			else if (op == 2) {
				cur_id = AccSer.SignUp(accounts, visacards, mastercards);
			}
			else if (op == 3) {
				return;
			}
			else cout << "ERROR!!\n";
		}

		cout << "1 : Send money \n";
		cout << "2 : Change default card in account \n";
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
			CardSer.SendMony(accounts[cur_id], accounts, operations, visacards, mastercards);
		}
		else if (op == 2) {
			AccSer.ChangeDefultCard(accounts[cur_id], visacards, mastercards);
		}
		else if (op == 3) {
			AccSer.AddVisaCard(accounts[cur_id], visacards);
		}
		else if (op == 4) {
			AccSer.AddMasterCard(accounts[cur_id], mastercards);
		}
		else if (op == 5) {
			CardSer.RemoveCard(accounts[cur_id], visacards, mastercards);
		}
		else if (op == 6) {
			CardSer.ShowCardData(accounts[cur_id], visacards, mastercards, operations);
		}
		else if (op == 7) {
			CardSer.ShowMyTrans(accounts[cur_id], operations);
		}
		else if (op == 8) {
			CardSer.ChangPassword(accounts[cur_id], visacards, mastercards);
		}
		else if (op == 9) {
			cur_id = -1;
		}
		else cout << "ERROR!!\n";
		UploadData();
	}
}