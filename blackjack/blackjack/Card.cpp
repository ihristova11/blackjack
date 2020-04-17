#include "Card.h"

bool Card::getDrawn() const
{
	return this->drawn;
}

CardSuit Card::getCardSuit() const
{
	return this->cardSuit;
}

CardType Card::getCardType() const
{
	return this->cardType;
}

void Card::setDrawn(bool isDrawn)
{
	this->drawn = isDrawn;
}

std::ostream& Card::print(std::ostream& out) const
{
	// out << this->cardType << "(" << this->cardSuit << ")";
	return out;
}
