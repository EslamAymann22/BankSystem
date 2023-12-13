#pragma once

class TypeCard {
public:
	bool IsVisa;
	int ID;
	TypeCard(bool IsVisa = 0, int ID = 0) :IsVisa(IsVisa), ID(ID) {}
};