#include "Deck.h"
#include "Constants.h"
#include <cmath>
#include <time.h>

Deck::Deck() : serialNumber("Default"), numberOfCards(Constants::DeckDefault)
{
	this->add_cards(Constants::DeckDefault);
}

Deck::Deck(const int& k, const char* s)
	: numberOfCards(k)
{
	this->add_cards(k);

	strcpy_s(this->serialNumber, strlen(s) + 1, s);
}

Deck& Deck::operator=(const Deck& other)
{
	strcpy_s(this->serialNumber, strlen(other.serialNumber) + 1, other.serialNumber);
	this->numberOfCards = other.numberOfCards;
	for (size_t i = 0; i < Constants::DeckMaxLenSN; i++)
	{
		this->cards[i] = other.cards[i];
	}

	return *this;
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
	size_t desired = Constants::PlayerMaxScore - score;
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
	this->numberOfCards = count;
	int ind;
	for (size_t d = 0; d < Constants::DeckMax; d++)
	{
		for (size_t s = 0; s < Constants::DeckCSuit; s++)
		{
			for (size_t t = 0; t < Constants::DeckCType; t++)
			{
				ind = d * Constants::DeckDefault + s * Constants::DeckCType + t;
				this->cards[ind] =
					Card(static_cast<CardSuit>(s),
						static_cast<CardType>(t),
						this->serialNumber + ind);
			}
		}
	}

	for (size_t i = count; i < Constants::DeckMaxCards; i++)
	{
		this->cards[i] = Card(CardSuit::None, CardType::NONE, "");
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
