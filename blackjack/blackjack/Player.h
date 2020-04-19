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

	int get_score() const;
	void update_coeff();
	void update_statistics(bool win);

	char name[Constants::PlayerMaxNameLen];
	Player& add_card(const Card&, const Rules&);
	std::ostream& print_drawn(std::ostream&) const;
	std::ostream& print_player(std::ostream&) const;

private:
	int age;
	int wins;
	int games;
	double coefficient;
	int score;

	Card drawnCards[Constants::PlayerMaxDrawn];
	int drawnLen;

	void copy_internals(const Player&);
};

#endif // !PLAYER_H
