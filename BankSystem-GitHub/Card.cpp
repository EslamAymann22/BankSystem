#include "Card.h"

void Card::operator+=(double amount) {
	this->Mony += amount;
}

void Card::operator-=(double amount) {
	this->Mony -= amount;
}

void Card::Changepassword(string NewPassword) {
	this->CardPIN = NewPassword;
}

Card::Card() {
	ZipCode = 0;
	Mony = 0;
}