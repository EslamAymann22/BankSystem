#pragma once
#include"Card.h"
#include"VisaCard.h"
#include"MAsterCard.h"
#include"TypeCard.h"
#include"Account.h"
#include"Operation.h"
class CardServes {
	Card* ChooseCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	Card* ChooseReceiverCard(vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	int AddTrans(string from, string to, double amount, vector<Operation>& operations);
	int getIdReceiver(Card* card, vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	double GetAmount(Card* senderCard);
	bool ValidInput(string cardnum, int cnt);
public:

	void SendMony(Account& account, vector<Account>& accounts,
		vector<Operation>& operations, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	void ChangPassword(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);
	void ShowMyTrans(Account& account, vector<Operation>& operations);
	void ShowMyTrans(Account& account, Card* card, vector<Operation>& operations);
	void ShowCardData(Account& account, vector<VisaCard>& visacards,
		vector<MasterCard>& mastercards, vector<Operation>& operations);
	void RemoveCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards);

};
