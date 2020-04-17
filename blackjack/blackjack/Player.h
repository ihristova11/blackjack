#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
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

	char* name; // dynamic memory

	std::ostream& printDrawn(std::ostream&) const;

private:
	unsigned int age;
	unsigned int wins;
	double coefficient;
	unsigned int score;

	Card* drawnCards;
	size_t drawnLen;

	void copyData(const Player&);
};

#endif // !PLAYER_H
