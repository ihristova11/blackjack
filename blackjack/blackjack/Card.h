#ifndef CARD_H
#define CARD_H

#include "CardSuit.h"
#include "CardType.h"
#include <ostream>

class Card
{
public: 
	Card(CardSuit, CardType, const char*);

	bool getDrawn() const;
	CardSuit getCardSuit() const;
	CardType getCardType() const;

	void setDrawn(bool);

	std::ostream& print(std::ostream&) const;
private:
	CardSuit cardSuit;
	CardType cardType;
	char serialNumber[16]; // to do: constant

	bool drawn;
};

#endif // !CARD_H
