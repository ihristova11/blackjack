#ifndef RULES_H
#define RULES_H

class Rules
{
public: 
	Rules();
	~Rules();

	void setCardPoints(const int*);
	int getCardPoints(int index);

private:
	int cardPoints[13];
};

#endif // !RULES_H
