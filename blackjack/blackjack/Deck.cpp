#include "Deck.h"
#include <cmath>
#include <cstring>
#include <time.h>

Deck::Deck() : serialNumber("Default"), cardsCount(Constants::DeckDefault)
{
	this->addCards(Constants::DeckDefault);
}

Deck::Deck(const int& k, const char* s = "Custom")
	: cardsCount(k)
{
	strcpy_s(this->serialNumber, strlen(s) + 1, s);
	this->addCards(k);
}

Deck::Deck(const Deck& other)
{
	this->copyInternals(other);
}

Deck& Deck::operator=(const Deck& other)
{
	if (this != &other)
	{
		this->copyInternals(other);
	}

	return *this;
}

Card Deck::draw()
{
	this->cards[0].setDrawn(true);
	Card first = this->cards[0];

	for (int i = 1; i < this->cardsCount; i++)
	{
		this->cards[i - 1] = this->cards[i];
	}

	this->cards[this->cardsCount - 1] = first;

	return first;
}

Deck& Deck::swap(const int& first, const int& second)
{
	if (valid(first) && valid(second))
	{
		Card temp = this->cards[first - 1];
		this->cards[first - 1] = this->cards[second - 1];
		this->cards[second - 1] = temp;
	}

	return *this;
}

int Deck::suit_count(const CardSuit& cs) const
{
	int len = this->cardsCount;
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

int Deck::rank_count(const CardType& ct) const
{
	int count = 0;

	for (int i = 0; i < this->cardsCount; i++)
	{
		if (!this->cards[i].getDrawn() && this->cards[i].getCardType() == ct)
		{
			++count;
		}
	}
	return count;
}

double Deck::calcProbability(const int& score, const Rules& rules) const
{
	double probability = 0;
	int desired = Constants::PlayerMaxScore - score;
	int count = 0;
	for (int i = 0; i < this->cardsCount; i++)
	{
		if (!this->cards[i].getDrawn() && desired ==
			rules.getPoints(this->cards[i].getCardType(), score))
		{
			++count;
		}
	}
	probability = static_cast<double>(count) / countDrawn();

	return probability;
}

int Deck::countDrawn() const
{
	int count = 0;

	for (int i = 0; i < this->cardsCount; i++)
	{
		if (!this->cards[i].getDrawn())
		{
			++count;
		}
	}

	return count;
}

void Deck::addCards(const int& count)
{
	this->cardsCount = count;
	int ind;
	int len;
	char serialToPass[Constants::CardMaxLenSN];
	for (int d = 0; d < Constants::DeckMax; d++)
	{
		for (int s = 0; s < Constants::DeckCSuit; s++)
		{
			for (int t = 0; t < Constants::DeckCType; t++)
			{
				ind = d * Constants::DeckDefault + s * Constants::DeckCType + t;
				len = strlen(this->serialNumber);

				strcpy_s(serialToPass, len + 1, this->serialNumber);
				serialToPass[len] = (char)ind;
				serialToPass[len + 1] = '\0';


				this->cards[ind] =
					Card(static_cast<CardSuit>(s),
						static_cast<CardType>(t),
						serialToPass);
			}
		}
	}

	for (int i = count; i < Constants::DeckMaxCards; i++)
	{
		this->cards[i] = Card(CardSuit::None, CardType::NONE, "");
	}

	this->shuffle();
}

void Deck::shuffle()
{
	int size = this->cardsCount;

	srand(time(NULL));

	for (int i = size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);

		this->swap(i, j);
	}
}

void Deck::copyInternals(const Deck& other)
{
	strcpy_s(this->serialNumber, strlen(other.serialNumber) + 1, other.serialNumber);
	this->cardsCount = other.cardsCount;
	for (int i = 0; i < Constants::DeckMaxCards; i++)
	{
		this->cards[i] = other.cards[i];
	}
}

bool Deck::valid(const int& index) const
{
	return index - 1 >= 0 && index - 1 < this->cardsCount;
}
