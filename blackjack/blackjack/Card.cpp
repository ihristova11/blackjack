#include "Card.h"

Card::Card() : cardSuit(CardSuit::None), cardType(CardType::NONE), serialNumber("")
{ }

Card::Card(const CardSuit& cs, const CardType& ct, const char* serialNumber) :
	cardSuit(cs), cardType(ct), drawn(false)
{
	strcpy_s(this->serialNumber, strlen(serialNumber) + 1, serialNumber);
}

Card::Card(const Card& other)
{
	this->copyInternals(other);
}

Card& Card::operator=(const Card& other)
{
	if (this != &other)
	{
		copyInternals(other);
	}

	return *this;
}

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
	switch (this->cardType)
	{
		case CardType::TWO: out << "2"; break;
		case CardType::THREE:out << "3"; break;
		case CardType::FOUR: out << "4"; break;
		case CardType::FIVE: out << "5"; break;
		case CardType::SIX:	 out << "6"; break;
		case CardType::SEVEN:out << "7"; break;
		case CardType::EIGHT:out << "8"; break;
		case CardType::NINE: out << "9"; break;
		case CardType::TEN:	 out << "10"; break;
		case CardType::ACE:	 out << "Ace"; break;
		case CardType::KING: out << "King"; break;
		case CardType::QUEEN:out << "Queen"; break;
		case CardType::JACK: out << "Jack"; break;
	}
	out << "(";
	switch (this->cardSuit)
	{
		case CardSuit::Clubs: out << "Clubs"; break;
		case CardSuit::Diamonds: out << "Diamonds"; break;
		case CardSuit::Hearts: out << "Hearts"; break;
		case CardSuit::Spades: out << "Spades"; break;
	}

	out << ")";

	return out;
}

void Card::copyInternals(const Card& other)
{
	this->cardSuit = other.cardSuit;
	this->cardType = other.cardType;
	this->drawn = other.drawn;
	strcpy_s(this->serialNumber, strlen(other.serialNumber) + 1, other.serialNumber);
}
