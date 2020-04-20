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
	Deck& swap(const int&, const int&);
	int suit_count(const CardSuit&) const;
	int rank_count(const CardType&) const;

	double calcProbability(const int&, const Rules&) const;

private:
	Card cards[Constants::DeckMaxCards];
	char serialNumber[Constants::DeckMaxLenSN];
	int cardsCount;

	int countDrawn() const;
	bool valid(const int&) const;

	void addCards(const int&);
	void shuffle();
	void copyInternals(const Deck&);
};

#endif // !DECK_H
