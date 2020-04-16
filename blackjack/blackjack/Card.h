#ifndef CARD_H
#define CARD_H

#include "CardSuit.h"
#include "CardType.h"

class Card
{
public: 
	CardSuit cardSuit;
	CardType cardType;
	char serialNumber[16]; // to do: constant
};

#endif // !CARD_H
