#pragma once
#include<bits/stdc++.h>
#include"User.h"
#include"TypeCard.h"

class Account : public User {
public:
	TypeCard DefultCard;
	string IPA_Num;
	int NumberOfVisaCardsInAccount;
	vector<int>MyVisaCards;
	int NumberOfMasterCardsInAccount;
	vector<int>MyMasterCards;
	int NumberOfTransInAccount;
	vector<int>MyTrans;
	Account();
};