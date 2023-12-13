#include "CardServes.h"

Card* CardServes::ChooseCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards) {
	int ch = 0;
	while (ch < 1) {
		int id = 1;
		for (auto it : account.MyVisaCards) {
			cout << id++ << ' ' << visacards[it].CardNum << '\n';
		}
		for (auto it : account.MyMasterCards) {
			cout << id++ << ' ' << mastercards[it].CardNum << '\n';
		}

		cout << "Enter id card : "; cin >> ch;
		if (ch >= id)ch = -1;
		if (id == 1) {
			ch = -5; break;
		}
	}
	ch--;
	if (ch < account.MyVisaCards.size() and ch>-1) {
		return &visacards[account.MyVisaCards[ch]];
	}
	else if (ch > -1) {
		ch -= account.MyVisaCards.size();
		return &mastercards[account.MyMasterCards[ch]];
	}
	cout << "You havn't any card in your account \n";
	return &visacards[0];
}

Card* CardServes::ChooseReceiverCard(vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	string card;
	while (1) {
		cout << "Enter Number of card or IPA Account";
		cin >> card;
		if (card.size() == 6) {
			for (Account& it : accounts) {
				if (it.IPA_Num == card) {
					if (it.DefultCard.IsVisa) {
						return &visacards[it.DefultCard.ID];
					}
					else {
						return &mastercards[it.DefultCard.ID];
					}
				}
			}
		}
		else if (card.size() == 16) {
			string bankname;
			cout << "Enter Bank name"; cin >> bankname;
			for (VisaCard& it : visacards) {
				if (it.CardNum == card and it.BankName == bankname)return &it;
			}
			for (MasterCard& it : mastercards) {
				if (it.CardNum == card and it.BankName == bankname)return &it;
			}
		}
	}
}

int CardServes::AddTrans(string from, string to, double amount, vector<Operation>& operations) {
	operations.push_back(Operation());
	operations.back().From = from;
	operations.back().To = to;
	operations.back().AmountOfMomy = amount;
	return operations.size() - 1;
}

int CardServes::getIdReceiver(Card* card, vector<Account>& accounts, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	int ret = -1;
	for (auto it : accounts) {
		ret++;
		for (int it2 : it.MyVisaCards) {
			if (visacards[it2].CardNum == card->CardNum)return ret;
		}
		for (int it2 : it.MyMasterCards) {
			if (mastercards[it2].CardNum == card->CardNum)return ret;
		}
	}
}

double CardServes::GetAmount(Card* senderCard) {
	double AmountOfMony = 0, ok = 0;
	while (!senderCard->CanSend(AmountOfMony)) {
		if (ok)cout << "Unvalid number\n";
		cout << "Your mony = " << senderCard->Mony << '\n';
		cout << "Enter amount of mony want send : "; cin >> AmountOfMony;
		ok = 1;
	}
	return AmountOfMony;
}

bool CardServes::ValidInput(string cardnum, int cnt) {
	for (auto it : cardnum) {
		if (it >= '0' and it <= '9')continue;
		return 0;
	}
	return (cardnum.size() == cnt);
}

void CardServes::SendMony(Account& account, vector<Account>& accounts, vector<Operation>& operations, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	Card* receiverCard;
	Card* senderCard;
	senderCard = ChooseCard(account, visacards, mastercards);
	receiverCard = ChooseReceiverCard(accounts, visacards, mastercards);
	int idReceiver = getIdReceiver(receiverCard, accounts, visacards, mastercards);
	if (senderCard == receiverCard)return cout << "\n\nyou cant send mony to same card!!\n", void();
	double amount = GetAmount(senderCard);
	senderCard->SendMony(receiverCard, amount);
	account.MyTrans.push_back(AddTrans(senderCard->CardNum, receiverCard->CardNum, amount, operations));
	account.NumberOfTransInAccount = account.MyTrans.size();
	accounts[idReceiver].MyTrans.push_back(operations.size() - 1);
	accounts[idReceiver].NumberOfTransInAccount = accounts[idReceiver].MyTrans.size();
	cout << "\n\nSuccesful !!\n\n";
}

void CardServes::ChangPassword(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	Card* card = ChooseCard(account, visacards, mastercards);
	string pin = "";
	while (pin.empty()) {
		cout << "Enter old card PIN : "; cin >> pin;
		if (pin == card->CardPIN)break;
		pin = "";
	}

	pin = "";
	while (pin.empty()) {
		cout << "Enter new pin : "; cin >> pin;
		if (ValidInput(pin, 4))break;
		pin = "";
	}
	card->CardPIN = pin;

}

void CardServes::ShowMyTrans(Account& account, vector<Operation>& operations)
{
	for (auto it : account.MyTrans) {
		cout << "From : " << operations[it].From << "  To  " << operations[it].To << " Send " << operations[it].AmountOfMomy << " $\n";
	}
}

void CardServes::ShowMyTrans(Account& account, Card* card, vector<Operation>& operations)
{
	for (auto it : account.MyTrans) {
		if (operations[it].From != card->CardNum and operations[it].To != card->CardNum)continue;
		cout << "From : " << operations[it].From << "  To  " << operations[it].To << " Send " << operations[it].AmountOfMomy << " $\n";
	}
}

void CardServes::ShowCardData(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards, vector<Operation>& operations)
{
	Card* card = ChooseCard(account, visacards, mastercards);
	cout << "Card name : " << card->CardName << '\n';
	cout << "Bank Name of card : " << card->BankName << '\n';
	cout << "PIN Card : " << card->CardPIN << '\n';
	cout << "Card number : " << card->CardNum << '\n';
	cout << "Card CVV : " << card->CVV << '\n';
	cout << "Card Expired Date : " << card->ExpDate.day << '/' << card->ExpDate.month << '/' << card->ExpDate.year << '\n';
	cout << "Card many : " << card->Mony << " $" << '\n';
	cout << "ZIP code of card : " << card->ZipCode << '\n';
	cout << "phone of card : " << card->PhoneNumber << '\n';
	cout << "\n\n\n\nYour trans \n\n\n";
	ShowMyTrans(account, card, operations);
}

void CardServes::RemoveCard(Account& account, vector<VisaCard>& visacards, vector<MasterCard>& mastercards)
{
	if (account.MyMasterCards.size() + account.MyVisaCards.size() < 2) {
		cout << "\n\nYou must have at least 2 account2\n\n";
		return;
	}
	Card* card = ChooseCard(account, visacards, mastercards);
	for (int i = 0; i < account.MyMasterCards.size(); i++) {
		if (mastercards[account.MyMasterCards[i]].CardNum == card->CardNum) {


			if (account.MyMasterCards[i] == account.DefultCard.ID and account.DefultCard.IsVisa == 0) {
				if (account.MyVisaCards.size() > 0) {
					account.DefultCard = TypeCard(1, account.MyVisaCards.front());
				}
				else if (account.MyMasterCards.size() > 1) {
					account.DefultCard = TypeCard(0, account.MyMasterCards.front());
				}
			}

			account.MyMasterCards.erase(account.MyMasterCards.begin() + i, account.MyMasterCards.begin() + i + 1);
			account.NumberOfMasterCardsInAccount--;

			break;
		}
	}
	for (int i = 0; i < account.MyVisaCards.size(); i++) {
		if (visacards[account.MyVisaCards[i]].CardNum == card->CardNum) {


			if (account.MyVisaCards[i] == account.DefultCard.ID and account.DefultCard.IsVisa == 1) {

				if (account.MyVisaCards.size() > 1) {
					account.DefultCard = TypeCard(1, account.MyVisaCards.front());
				}
				else if (account.MyMasterCards.size() > 0) {
					account.DefultCard = TypeCard(0, account.MyMasterCards.front());
				}

			}

			account.MyVisaCards.erase(account.MyVisaCards.begin() + i, account.MyVisaCards.begin() + i + 1);
			account.NumberOfVisaCardsInAccount--;
			break;
		}
	}
}
