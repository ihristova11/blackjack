#include "Rules.h"

Rules::Rules() : cardPoints{}
{
}

Rules::~Rules()
{
}

void Rules::setCardPoints(const int* arr)
{
	for (size_t i = 0; i < 13; i++) // const
	{
		this->cardPoints[i] = arr[i];
	}
}

int Rules::getCardPoints(int index)
{
	return this->cardPoints[index];
}
