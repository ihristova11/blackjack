#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Rules.h"
#include <ostream>

class Player
{
public:
	Player();
	Player(const Player&);
	Player(const char*);
	Player(const char*, const size_t&, const double&);
	Player& operator=(const Player&);

	~Player();

	int getScore() const;

	char name[100];
	Player& addCard(const Card&, const Rules&);
	std::ostream& printDrawn(std::ostream&) const;
	std::ostream& printPlayer(std::ostream&) const;

private:
	unsigned int age;
	unsigned int wins;
	double coefficient;
	unsigned int score;

	Card drawnCards[104];
	size_t drawnLen;

	void copyData(const Player&);
};

#endif // !PLAYER_H
