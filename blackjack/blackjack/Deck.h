#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck
{
public:
	Deck() = default;
	Deck(const size_t&, const char*);

	Card draw();  // return type? Card&
	Deck& swap(size_t, size_t); // chaining

	size_t suit_count(CardSuit) const;
	size_t rank_count(CardType) const;

private:
	Card* cards; // dynamically allocated
	char serialNumber[11]; // todo: constant
	size_t numberOfCards;

	bool isValid(size_t) const;
};

#endif // !DECK_H
