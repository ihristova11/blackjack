#include "Deck.h"

Deck::Deck(const size_t& k, const char* s = "Custom")
{ 
	// todo implement
}

Card Deck::draw()
{
	size_t len = this->numberOfCards;

	Card first = this->cards[0];
	
	for (size_t i = 1; i < len; i++)
	{
		this->cards[i - 1] = this->cards[i];
	}

	this->cards[len - 1] = first;

	return first;
}

Deck& Deck::swap(size_t first, size_t second)
{
	if (isValid(first) && isValid(second))
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
		if (!this->cards[i].getIsInPlayer() && this->cards[i].getCardType() == ct)
		{
			++count;
		}
	}
	return count;
}

bool Deck::isValid(size_t index) const
{
	return index - 1 >= 0 && index - 1 < this->numberOfCards;
}
