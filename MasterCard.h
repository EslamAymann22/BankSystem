#pragma once
#include<bits/stdc++.h>
#include"Card.h"
using namespace std;
class MasterCard : public Card {
public:
	double tax = 0;
	void SendMony(Card* receiver, double amount);
	bool CanSend(double c);
};