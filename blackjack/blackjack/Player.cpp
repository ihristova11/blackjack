#include "Player.h"
#include <cstring>

Player::Player()
	: age(18), wins(0), coefficient(0), score(0), drawnCards(), drawnLen(0)
{}

Player::Player(const Player& other)
{
	copy_internals(other);
}

Player::Player(const char* name) :
	age(18),
	wins(0),
	coefficient(0),
	score(0),
	drawnCards(),
	drawnLen(0)
{
	strcpy_s(this->name, strlen(name) + 1, name);
}

Player::Player(const char* name, const size_t& wins, const double& coefficient) :
	age(18), // constant 
	wins(wins),
	coefficient(coefficient),
	score(0),
	drawnCards(),
	drawnLen(0)
{
	strcpy_s(this->name, strlen(name) + 1, name);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		copy_internals(other);
	}

	return *this;
}

Player::~Player()
{
}

int Player::get_score() const
{
	return this->score;
}

Player& Player::add_card(const Card& card, const Rules& rules)
{
	this->drawnCards[drawnLen] = card;
	++drawnLen;

	// update points
	this->score += rules.getCardPoints(card.getCardType());

	return *this;
}

std::ostream& Player::print_drawn(std::ostream& out) const
{
	for (size_t i = 0; i < drawnLen; i++)
	{
		this->drawnCards[i].print(out) << " ";
	}

	out << "Points(" << this->score << ")" << std::endl;

	return out;
}

std::ostream& Player::print_player(std::ostream& out) const
{
	out << this->name << " " << this->wins << " " << this->coefficient;

	return out;
}

void Player::copy_internals(const Player& other)
{
	strcpy_s(this->name, strlen(other.name) + 1, other.name);
	this->age = other.age;
	this->coefficient = other.coefficient;
	this->score = other.score;
	this->wins = other.wins;
	this->drawnLen = other.drawnLen;
	for (size_t i = 0; i < other.drawnLen; i++)
	{
		this->drawnCards[i] = other.drawnCards[i];
	}
}
