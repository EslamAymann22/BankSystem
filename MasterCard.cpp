#include "MasterCard.h"

void MasterCard::SendMony(Card* receiver, double amount) {
	*this -= amount + amount * tax;
	*receiver += amount;
}

bool MasterCard::CanSend(double c) {
	return (c > 0 and (c + c * tax) <= this->Mony);
}