#include "Card.h"

bool Card::getIsInPlayer() const
{
	return this->isInPlayer;
}

CardSuit Card::getCardSuit() const
{
	return this->cardSuit;
}

CardType Card::getCardType() const
{
	return this->cardType;
}
