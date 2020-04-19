#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include "Rules.h"

class Game
{
public:
	Game();
	~Game();

	void start();

	void print_players(const Player* players, int n);
	void save_players(const Player* players, int n);

private:
	Player* players;
	Deck deck;
	Rules rules;

	void init();
	void load_players(Player* players, int n);
	void seed_players();
};

#endif // !GAME_H
