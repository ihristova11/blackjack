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
	drawnCount(0)
{}

Player::Player(const Player& other)
{
	copyInternals(other);
}

Player::Player(const char* name) :
	name(""),
	age(Constants::PlayerDefaultAge),
	wins(0),
	games(0),
	coefficient(0),
	score(0),
	drawnCards(),
	drawnCount(0)
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
	drawnCount(0)
{
	strcpy_s(this->name, strlen(name) + 1, name);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		copyInternals(other);
	}

	return *this;
}

int Player::getScore() const
{
	return this->score;
}

void Player::updateCoeff()
{
	this->coefficient = static_cast<double>(this->wins) / this->games;
}

void Player::updateStatistics(bool win)
{
	if (win)
	{
		this->wins++;
	}
	this->games++;
	this->updateCoeff();
}

void Player::clearActivity()
{
	for (int i = 0; i < this->drawnCount; i++)
	{
		this->drawnCards[i] = Card();
	}
	this->drawnCount = 0;
	this->score = 0;
}

Player& Player::addCard(const Card& card, const Rules& rules)
{
	this->drawnCards[drawnCount] = card;
	++drawnCount;

	// update points
	this->score += rules.getPoints(card.getCardType(), this->score);

	return *this;
}

std::ostream& Player::printDrawn(std::ostream& out) const
{
	for (int i = 0; i < drawnCount; i++)
	{
		this->drawnCards[i].print(out) << " ";
	}

	out << "Points(" << this->score << ")" << std::endl;

	return out;
}

std::ostream& Player::printPlayer(std::ostream& out) const
{
	out << name << " " << wins << " " << coefficient;

	return out;
}

void Player::copyInternals(const Player& other)
{
	strcpy_s(this->name, strlen(other.name) + 1, other.name);
	this->age = other.age;
	this->coefficient = other.coefficient;
	this->score = other.score;
	this->wins = other.wins;
	this->games = other.games;
	this->drawnCount = other.drawnCount;
	for (size_t i = 0; i < other.drawnCount; i++)
	{
		this->drawnCards[i] = other.drawnCards[i];
	}
}
