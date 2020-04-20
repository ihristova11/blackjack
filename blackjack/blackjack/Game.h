#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"

class Game {
public:
	~Game();

	Player* loaded;
	Deck deck;
	Rules rules;

	Player player;
	Player dealer;
	
	int playersCount;

	void start();
	void init();

private:
	int playerIndex;
	bool customPlayerGame;

	void initPlayer();
	void initDeck();
	void initRules();

	void loadPlayers();
	int countRecords();
	void printPlayers();
	void saveBinary();
	void updateBinary();
};

#endif // !GAME_H
