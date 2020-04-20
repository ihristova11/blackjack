#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Rules.h"
#include "Constants.h"
#include <ostream>

class Player
{
public:
	Player();
	Player(const Player&);
	Player(const char*);
	Player(const char*, const  int&, const double&);
	Player& operator=(const Player&);

	char name[Constants::PlayerMaxNameLen];
	
	int getScore() const;
	void updateCoeff();
	void updateStatistics(bool win);
	void clearActivity();

	Player& addCard(const Card&, const Rules&);
	std::ostream& printDrawn(std::ostream&) const;
	std::ostream& printPlayer(std::ostream&) const;

private:
	int age;
	int wins;
	int games;
	double coefficient;
	int score;

	Card drawnCards[Constants::PlayerMaxDrawn];
	int drawnCount;

	void copyInternals(const Player&);
};

#endif // !PLAYER_H
