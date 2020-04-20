#ifndef RULES_H
#define RULES_H

#include "Constants.h"

class Rules
{
public:
	Rules();

	void setPoints(const int*);
	int getPoints(const int&, const int&) const;

private:
	int cardPoints[Constants::RulesCardPoints];
};

#endif // !RULES_H
