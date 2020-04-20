#include "Rules.h"
#include "CardType.h"
#include "Constants.h"

Rules::Rules() : cardPoints{}
{ }

void Rules::setPoints(const int* arr)
{
	for (int i = 0; i < Constants::DeckCType; i++)
	{
		this->cardPoints[i] = arr[i];
	}
}

int Rules::getPoints(const int& index, const int& score) const
{
	if (Constants::PlayerMaxScore - score >= 11 && index == CardType::ACE) { return 11; }
	return this->cardPoints[index];
}
