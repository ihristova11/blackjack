#ifndef CARD_H
#define CARD_H

#include "CardSuit.h"
#include "Constants.h"
#include "CardType.h"
#include <ostream>

class Card
{
public: 
	Card();
	Card(CardSuit, CardType, const char*);
	Card(const Card&);
	Card& operator=(const Card&);

	bool getDrawn() const;
	CardSuit getCardSuit() const;
	CardType getCardType() const;

	void setDrawn(bool);

	std::ostream& print(std::ostream&) const;
private:
	CardSuit cardSuit;
	CardType cardType;
	char serialNumber[Constants::CardMaxLenSN];

	bool drawn;
	void copy_internals(const Card&);
};

#endif // !CARD_H
