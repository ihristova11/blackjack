#include "Deck.h"
#include <cmath>
#include <time.h>

Deck::Deck() : serialNumber("Default"), numberOfCards(52)
{
	this->add_cards(52);
}

Deck::Deck(const int& k, const char* s)
	: cards(), numberOfCards(k)
{
	if (k == 52)
	{
		this->add_cards(k);
	}

	strcpy_s(this->serialNumber, strlen(s) + 1, s);
}

Card Deck::draw()
{
	this->cards[0].setDrawn(true);
	Card first = this->cards[0];

	for (size_t i = 1; i < this->numberOfCards; i++)
	{
		this->cards[i - 1] = this->cards[i];
	}

	this->cards[this->numberOfCards - 1] = first;

	return first;
}

Deck& Deck::swap(int first, int second)
{
	if (valid(first) && valid(second))
	{
		Card temp = this->cards[first - 1];
		this->cards[first - 1] = this->cards[second - 1];
		this->cards[second - 1] = temp;
	}

	return *this;
}

size_t Deck::suit_count(CardSuit cs) const
{
	int len = this->numberOfCards;
	int count = 0;

	for (int i = 0; i < len; i++)
	{
		if (this->cards[i].getCardSuit() == cs)
		{
			++count;
		}
	}

	return count;
}

size_t Deck::rank_count(CardType ct) const
{
	int count = 0;

	for (size_t i = 0; i < this->numberOfCards; i++)
	{
		if (!this->cards[i].getDrawn() && this->cards[i].getCardType() == ct)
		{
			++count;
		}
	}
	return count;
}

double Deck::find_probability(const int& score) const
{
	double probability = 0;
	size_t desired = 21 - score;
	int count = 0;
	for (size_t i = 0; i < this->numberOfCards; i++)
	{
		if (!this - cards[i].getDrawn() && this->cards[i].getCardType() == desired) // should be updated
		{
			++count;
		}
	}
	probability = count / find_drawn();

	return probability;
}

int Deck::find_drawn() const
{
	int count = 0;

	for (size_t i = 0; i < this->numberOfCards; i++)
	{
		if (!this->cards[i].getDrawn())
		{
			++count;
		}
	}

	return count;
}

void Deck::add_cards(int count) // improve
{
	int suits = static_cast<int>(ceil(count / 13.0));

	for (size_t cardSuit = 0; cardSuit < suits; cardSuit++)
	{
		for (size_t cardType = 0; (cardSuit * 13 + cardType) < 13; cardType++)
		{
			this->cards[cardSuit * 13 + cardType] =
				Card(static_cast<CardSuit>(cardSuit),
					static_cast<CardType>(cardType),
					this->serialNumber + cardSuit * 13 + cardType);
		}
	}

	this->shuffle();
}

void Deck::shuffle()
{
	int size = this->numberOfCards;
	
	srand(time(NULL));

	for (int i = size - 1; i > 0; i--)
	{ 
		int j = rand() % (i + 1);

		swap(i, j);
	}
}

bool Deck::valid(int index) const
{
	return index - 1 >= 0 && index - 1 < this->numberOfCards;
}
