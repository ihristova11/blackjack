#include "Player.h"
#include <cstring>

Player::Player()
	: name(nullptr), age(18), wins(0), coefficient(0), score(0), drawnCards(nullptr), drawnLen(0)
{}

Player::Player(const char* name) :
	name(new char[strlen(name) + 1]),
	age(18),
	wins(0),
	coefficient(0),
	score(0),
	drawnCards(nullptr),
	drawnLen(0)
{
	strcpy_s(this->name, strlen(name) + 1, name);
}

Player::Player(const char* name, const size_t& wins, const double& coefficient) :
	name(new char[strlen(name) + 1]),
	age(18), // constant 
	wins(wins),
	coefficient(coefficient),
	score(0),
	drawnCards(nullptr),
	drawnLen(0)
{
	strcpy_s(this->name, strlen(name) + 1, name);
}

Player::~Player()
{
	delete[] name;
	delete[] drawnCards;
}

std::ostream& Player::printDrawn(std::ostream& out) const
{
	for (size_t i = 0; i < drawnLen; i++)
	{
		this->drawnCards[i].print(out) << " ";
	}

	out << "Points(" << this->score << ")" << std::endl;

	return out;
}