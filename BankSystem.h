#pragma once
#include<bits/stdc++.h>
#include"Account.h"
#include"MasterCard.h"
#include"VisaCard.h"
#include"Operation.h"
#include"CardServes.h"
#include"AccountServes.h"
#include"AddDataToDataBase.h"
using namespace std;

class BankSystem
{
	vector<Account>accounts;
	vector<VisaCard>visacards;
	vector<MasterCard>mastercards;
	vector<Operation>operations;
	
	bool FoundFile(ifstream& fin);
	bool FoundFile(ofstream& fin);

	void DownloadData();

	void UploadData();
	public:
		BankSystem();

	AccountServes AccSer;
	CardServes CardSer;
	AddDataToDataBase AddData;

	void RunSystem();

	~BankSystem() {
		UploadData();
	}
};

