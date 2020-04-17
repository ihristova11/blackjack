#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck
{
public:
	Deck();
	Deck(const int&, const char* = "Custom");

	Card draw();
	Deck& swap(int, int);

	size_t suit_count(CardSuit) const;
	size_t rank_count(CardType) const;

	double find_probability(const int&) const;
	int find_drawn() const;

private:
	Card cards[104]; // constant
	char serialNumber[11]; // todo: constant
	size_t numberOfCards;

	bool valid(int) const;

	void add_cards(int count);

	void shuffle();
};

#endif // !DECK_H
