#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"

class Game {
public:
	~Game();

	Player* players;
	Deck deck;
	Rules rules;

	Player player;
	Player dealer;
	
	int playersLen;

	void start();
	void init();

private:
	int playerIndex;
	bool customPlayer;

	void loadPlayersFromBin();
	int getRecordsLen();
	void printPlayers();
	void savePlayersToBin();
	void updateBinary();

	void initCurrentPlayer();
	void initDeck();
	void initRules();
};

#endif // !GAME_H
