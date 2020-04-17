#ifndef RULES_H
#define RULES_H

class Rules
{
public: 
	Rules();
	~Rules();

	void setCardPoints(const int*);
	int getCardPoints(const int& index) const;

private:
	int cardPoints[13];
};

#endif // !RULES_H
