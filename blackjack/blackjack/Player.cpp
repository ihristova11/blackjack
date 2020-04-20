#include "Player.h"
#include <cstring>

Player::Player()
	: name(""),
	age(Constants::PlayerDefaultAge),
	wins(0),
	games(0),
	coefficient(0),
	score(0),
	drawnCards(),
	drawnLen(0)
{}

Player::Player(const Player& other)
{
	copy_internals(other);
}

Player::Player(const char* name) :
	name(""),
	age(Constants::PlayerDefaultAge),
	wins(0),
	games(0),
	coefficient(0),
	score(0),
	drawnCards(),
	drawnLen(0)
{
	strcpy_s(this->name, strlen(name) + 1, name);
}

Player::Player(const char* name, const int& wins, const double& coefficient) :
	name(""),
	age(Constants::PlayerDefaultAge),
	wins(wins),
	games(0),
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

int Player::get_score() const
{
	return this->score;
}

void Player::update_coeff()
{
	this->coefficient = static_cast<double>(this->wins) / this->games;
}

void Player::update_statistics(bool win)
{
	if (win)
	{
		this->wins++;
	}
	this->games++;
	this->update_coeff();
}

void Player::erase_activity()
{
	for (int i = 0; i < this->drawnLen; i++)
	{
		this->drawnCards[i] = Card();
	}
	this->drawnLen = 0;
	this->score = 0;
}

Player& Player::add_card(const Card& card, const Rules& rules)
{
	this->drawnCards[drawnLen] = card;
	++drawnLen;

	// update points
	this->score += rules.getCardPoints(card.getCardType(), this->score);

	return *this;
}

std::ostream& Player::print_drawn(std::ostream& out) const
{
	for (int i = 0; i < drawnLen; i++)
	{
		this->drawnCards[i].print(out) << " ";
	}

	out << "Points(" << this->score << ")" << std::endl;

	return out;
}

std::ostream& Player::print_player(std::ostream& out) const
{
	out << name << " " << wins << " " << coefficient;

	return out;
}

void Player::copy_internals(const Player& other)
{
	strcpy_s(this->name, strlen(other.name) + 1, other.name);
	this->age = other.age;
	this->coefficient = other.coefficient;
	this->score = other.score;
	this->wins = other.wins;
	this->games = other.games;
	this->drawnLen = other.drawnLen;
	for (size_t i = 0; i < other.drawnLen; i++)
	{
		this->drawnCards[i] = other.drawnCards[i];
	}
}
