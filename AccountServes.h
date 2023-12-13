#pragma once
#include"VisaCard.h"
#include"MAsterCard.h"
#include"TypeCard.h"
#include"Account.h"
#include"Operation.h"
using namespace std;

class AccountServes {

	bool ValidGmail(string Gmail);
	bool UniqeGmail(string gmail, vector<Account>&accounts);
	string GetGmail(vector<Account>& accounts);
	bool ValidUser(string user);
	bool UniqeUser(string user, vector<Account>& accounts);
	int chickAccount(string username, string pass, vector<Account>& accounts);
	string GetUser(vector<Account>& accounts);
	string GetCard(int cnt);

	bool ValidInput(string cardnum, int cnt);
	int ChickVisaCard(VisaCard& card, vector<VisaCard>& visacards);
	int ChickMasterCard(MasterCard& card, vector<MasterCard>& mastercards);
	TypeCard ChooseDefultCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);

public:
	int LogIn(vector<Account>& accounts);
	int SignUp(vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	void ChangeDefultCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	void AddVisaCard(Account& account, vector<VisaCard>& visacards);
	void AddMasterCard(Account& account, vector<MasterCard>& mastercards);
};
