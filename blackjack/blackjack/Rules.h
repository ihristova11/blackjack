#ifndef RULES_H
#define RULES_H

#include "Constants.h"

class Rules
{
public: 
	Rules();
	~Rules();

	void setCardPoints(const int*);
	int getCardPoints(const int& index) const;

private:
	int cardPoints[Constants::RulesCardPoints];
};

#endif // !RULES_H
