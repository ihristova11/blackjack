#ifndef CARD_H
#define CARD_H

#include "CardSuit.h"
#include "CardType.h"

class Card
{
public: 
	Card() = default;
	Card(CardSuit, CardType);

	bool getIsInPlayer() const;
	CardSuit getCardSuit() const;
	CardType getCardType() const;

private:
	CardSuit cardSuit;
	CardType cardType;
	char serialNumber[16]; // to do: constant

	bool isInPlayer;
};

#endif // !CARD_H
