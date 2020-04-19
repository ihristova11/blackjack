#include "Rules.h"

Rules::Rules() : cardPoints{}
{ }

void Rules::setCardPoints(const int* arr)
{
	for (int i = 0; i < Constants::DeckCType; i++)
	{
		this->cardPoints[i] = arr[i];
	}
}

int Rules::getCardPoints(const int& index) const
{
	return this->cardPoints[index];
}
