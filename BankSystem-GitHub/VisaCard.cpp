#include "VisaCard.h"

void VisaCard::SendMony(Card* receiver, double amount) {
	*this -= amount;
	*receiver += amount;
}

bool VisaCard::CanSend(double c) {
	return (c > 0 and c <= this->Mony);
}