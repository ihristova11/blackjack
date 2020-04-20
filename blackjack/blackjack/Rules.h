#ifndef RULES_H
#define RULES_H

#include "Constants.h"

class Rules
{
public:
	Rules();

	void setCardPoints(const int*);
	int getCardPoints(const int&, const int&) const;

private:
	int cardPoints[Constants::RulesCardPoints];
};

#endif // !RULES_H
