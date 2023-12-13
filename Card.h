#pragma once
#include<bits/stdc++.h>
using namespace std;

class Card {
	class Date {
	public:
		int day;
		int month;
		int year;
	};
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
	void operator += (double amount);
	void operator -= (double amount);
	void Changepassword(string NewPassword);
	Card();
};

