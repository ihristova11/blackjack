#include "Rules.h"
#include "CardType.h"

Rules::Rules() : cardPoints{}
{ }

void Rules::setCardPoints(const int* arr)
{
	for (int i = 0; i < Constants::DeckCType; i++)
	{
		this->cardPoints[i] = arr[i];
	}
}

int Rules::getCardPoints(const int& index, const int& score) const
{
	if (21 - score > 11 && index == CardType::ACE) { return 11; }
	return this->cardPoints[index];
}
