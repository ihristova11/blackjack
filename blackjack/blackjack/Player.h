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
	Player(const char*, const size_t&, const double&);
	Player& operator=(const Player&);

	~Player();

	int get_score() const;

	char name[Constants::PlayerMaxNameLen];
	Player& add_card(const Card&, const Rules&);
	std::ostream& print_drawn(std::ostream&) const;
	std::ostream& print_player(std::ostream&) const;

private:
	unsigned int age;
	unsigned int wins;
	double coefficient;
	unsigned int score;

	Card drawnCards[Constants::PlayerMaxDrawn];
	size_t drawnLen;

	void copy_internals(const Player&);
};

#endif // !PLAYER_H
