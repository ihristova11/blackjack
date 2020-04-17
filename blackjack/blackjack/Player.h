#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <ostream>

class Player
{
public:
	Player();
	Player(const char*);
	Player(const char*, const size_t&, const double&);

	~Player();

	std::ostream& printDrawn(std::ostream&) const;
private:
	char* name; // dynamic memory
	unsigned int age;
	unsigned int wins;
	double coefficient;
	unsigned int score;

	Card* drawnCards;
	size_t drawnLen;
};

#endif // !PLAYER_H
