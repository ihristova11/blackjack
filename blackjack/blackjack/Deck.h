#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck
{
public:
	Deck() = default;
	Deck(size_t, char*);

	Card draw();  // return type? Card&
	Deck& swap(size_t, size_t); // chaining

	size_t suit_count(CardSuit) const;
	size_t rank_count(CardType) const;

private:
	Card cards[52]; // todo: constant
	char serialNumber[11]; // todo: constant
};

#endif // !DECK_H
