#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "Constants.h"
#include "Rules.h"

class Deck
{
public:
	Deck();
	Deck(const int&, const char*);
	Deck(const Deck&);
	Deck& operator=(const Deck&);

	Card draw();
	Deck& swap(int, int);

	int suit_count(CardSuit) const;
	int rank_count(CardType) const;

	double find_probability(const int&, const Rules&) const;
	int find_drawn() const;

private:
	Card cards[Constants::DeckMaxCards];
	char serialNumber[Constants::DeckMaxLenSN];
	int numberOfCards;

	bool valid(int) const;
	void add_cards(int count);
	void shuffle();
	void copy_internals(const Deck&);
};

#endif // !DECK_H
