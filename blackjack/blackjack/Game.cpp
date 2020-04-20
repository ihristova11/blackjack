#include "Game.h"
#include <iostream>
#include <fstream>

Game::~Game()
{
	delete[] this->players;
}

void Game::start()
{
	bool end = false;

	loadPlayersFromBin();
	printPlayers();

	init();

	// start game
	std::cout << "Start!" << std::endl;
	char command[13];

	this->player.add_card(deck.draw(), rules);
	this->player.print_drawn(std::cout);

	// engine
	while (!end)
	{
		std::cout << "Hit/Stand/Probability" << std::endl;
		std::cin.getline(command, 12);

		if (strcmp(command, "Hit") == 0)
		{
			// draw a card from the deck
			this->player.add_card(deck.draw(), rules);
			this->player.print_drawn(std::cout);

			if (this->player.get_score() > 21)
			{
				this->player.update_statistics(false);
				std::cout << "You lose!" << std::endl;
				end = true;
			}
		}
		else if (strcmp(command, "Stand") == 0)
		{
			// start dealer draw
			while (this->dealer.get_score() <= 17)
			{
				this->dealer.add_card(deck.draw(), rules);
			}

			std::cout << "The dealer’s draw: ";
			this->dealer.print_drawn(std::cout);

			if (this->dealer.get_score() > 21)
			{
				this->player.update_statistics(true);
				std::cout << "You won!" << std::endl;
			}
			else
			{
				// compare scores
				if (this->player.get_score() >= this->dealer.get_score())
				{
					this->player.update_statistics(true);
					std::cout << "You won!" << std::endl;
				}
				else
				{
					this->player.update_statistics(false);
					std::cout << "You lose!" << std::endl;
				}
			}
			end = true;
		}
		else if (strcmp(command, "Probability") == 0)
		{
			std::cout << deck.find_probability(this->player.get_score(), this->rules) << std::endl;
		}
		else
		{
			std::cerr << "Invalid command!" << std::endl;
			std::cerr << "Enter a valid one!" << std::endl;
		}
	}

	this->updateBinary();
}

void Game::init()
{
	this->initCurrentPlayer();

	std::cout << "You will play as " << this->player.name << "." << std::endl;

	this->initDeck();
	this->initRules();
}

void Game::loadPlayersFromBin()
{
	int n = getRecordsLen();
	this->players = new Player[n];
	this->playersLen = n;

	std::ifstream ifs;
	ifs.open("players.bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		std::cerr << "No players to choose from! Create a new player." << std::endl;
	}
	ifs.seekg(0);
	ifs.read((char*) & *this->players, sizeof(Player) * n);
	ifs.close();
}

int Game::getRecordsLen()
{
	int n;
	std::ifstream ifs;
	ifs.open("players.bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		return 0;
	}
	ifs.seekg(0, std::ios::end);

	n = ifs.tellg() / sizeof(Player);
	ifs.close();
	return n;
}

void Game::printPlayers()
{
	for (int i = 0; i < this->playersLen; i++)
	{
		this->players[i].print_player(std::cout) << std::endl;
	}
}

void Game::savePlayersToBin()
{
	std::ofstream ofs;
	ofs.open("players.bin", std::ios::out | std::ios::binary);
	if (!ofs)
	{
		std::cerr << "Not able to open binary!" << std::endl;
	}
	ofs.seekp(0, std::ios::beg);
	ofs.write((char*) & *this->players, sizeof(Player) * this->playersLen);
	ofs.close();
	std::cout << "All changes are saved successfully in the file!" << std::endl;
}

void Game::updateBinary()
{
	if (this->customPlayer)
	{
		Player* temp = new Player[this->playersLen + 1];
		for (int i = 0; i < this->playersLen; i++)
		{
			temp[i] = players[i];
		}
		// erase game activity before saving
		this->player.erase_activity();
		temp[this->playersLen] = this->player;
		this->playersLen++;

		delete[] this->players;
		this->players = new Player[this->playersLen];

		for (int i = 0; i < this->playersLen; i++)
		{
			this->players[i] = temp[i];
		}
		delete[] temp;

		savePlayersToBin();
	}
	else
	{
		this->player.erase_activity();
		this->players[this->playerIndex] = this->player;
		savePlayersToBin();
	}
}

void Game::initCurrentPlayer()
{
	std::cout << "Choose a player or enter a new player:" << std::endl;
	char name[99];
	std::cin.getline(name, 100);

	// check for a player with that name
	for (int i = 0; i < this->playersLen; i++)
	{
		if (strcmp(players[i].name, name) == 0)
		{
			this->player = this->players[i];
			this->playerIndex = i;
			break;
		}
	}

	if (strcmp(this->player.name, "") == 0)
	{
		// create a new player with that name
		this->player = Player(name);
		this->customPlayer = true;
	}
}

void Game::initDeck()
{
	std::cout << "To choose default deck, enter default." << std::endl;
	std::cout << "If you don't choose a default one, a custom deck will be created." << std::endl;

	char deck_type[11];
	std::cin.getline(deck_type, 11);

	if (strcmp(deck_type, "default") != 0)
	{
		int deckSize = 0;
		do
		{
			std::cout << "Choоse the size of the deck [50-104]:" << std::endl;
			std::cin >> deckSize;
			std::cin.ignore();
		} while (deckSize < 50 || deckSize > 104);

		this->deck = Deck(deckSize, "inputSN");
	}
}

void Game::initRules()
{
	int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 10, 10, 10 };
	this->rules.setCardPoints(points);
}
