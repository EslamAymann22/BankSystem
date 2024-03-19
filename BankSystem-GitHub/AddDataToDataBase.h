#pragma once
#include<bits/stdc++.h>
#include"Account.h"
#include"MasterCard.h"
#include"VisaCard.h"
#include"Operation.h"

using namespace std;

class AddDataToDataBase {

	vector<Account>accounts;
	vector<VisaCard>visacards;
	vector<MasterCard>mastercards;
	vector<Operation>operations;

	bool UniqeNum(string s);
	bool validPIN(string s, int n);
	string GetNum();
	string GetJustNum(int n);
public:

	void add(vector<Account>& accounts,
		vector<VisaCard>& visacards, vector<MasterCard>& mastercards,
		vector<Operation>& operations);
};