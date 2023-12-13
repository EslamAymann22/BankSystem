#pragma once
#include<bits/stdc++.h>
#include"Card.h"
using namespace std;

class VisaCard : public Card {
public:
	void SendMony(Card* receiver, double amount);
	bool CanSend(double c);
};