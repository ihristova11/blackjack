#include "Rules.h"
#include "Constants.h"

Rules::Rules() : cardPoints{}
{ }

Rules::~Rules()
{
}

void Rules::setCardPoints(const int* arr)
{
	for (size_t i = 0; i < Constants::DeckCSuit; i++)
	{
		this->cardPoints[i] = arr[i];
	}
}

int Rules::getCardPoints(const int& index) const
{
	return this->cardPoints[index];
}
