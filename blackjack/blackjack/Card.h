#ifndef CARD_H
#define CARD_H

#include "CardSuit.h"
#include "CardType.h"
#include "OwnerType.h"
#include <ostream>

class Card
{
public: 
	Card();
	Card(CardSuit, CardType, const char*);
	~Card();

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
	OwnerType owner;
};

#endif // !CARD_H
