#include "Game.h"
#include "Constants.h"

#include <iostream>
#include <fstream>

Game::~Game()
{
	delete[] this->loaded;
}

void Game::start()
{
	bool end = false;
	this->loadPlayers();
	this->printPlayers();
	this->init();

	// start game
	std::cout << "Start!" << std::endl;
	char command[Constants::GameMaxCommandLen];

	this->player.addCard(deck.draw(), rules);
	this->player.printDrawn(std::cout);

	// engine
	while (!end)
	{
		std::cout << "Hit/Stand/Probability" << std::endl;
		std::cin.getline(command, Constants::GameMaxCommandLen - 1);

		if (strcmp(command, "Hit") == 0)
		{
			// draw a card from the deck
			this->player.addCard(deck.draw(), rules);
			this->player.printDrawn(std::cout);

			if (this->player.getScore() > Constants::PlayerMaxScore)
			{
				this->player.updateStatistics(false);
				std::cout << "You lose!" << std::endl;
				end = true;
			}
		}
		else if (strcmp(command, "Stand") == 0)
		{
			// start dealer draw
			while (this->dealer.getScore() <= Constants::DealerMinScore)
			{
				this->dealer.addCard(deck.draw(), rules);
			}

			std::cout << "The dealer’s draw: ";
			this->dealer.printDrawn(std::cout);

			if (this->dealer.getScore() > Constants::PlayerMaxScore)
			{
				this->player.updateStatistics(true);
				std::cout << "You won!" << std::endl;
			}
			else
			{
				// compare scores
				if (this->player.getScore() >= this->dealer.getScore())
				{
					this->player.updateStatistics(true);
					std::cout << "You won!" << std::endl;
				}
				else
				{
					this->player.updateStatistics(false);
					std::cout << "You lose!" << std::endl;
				}
			}
			end = true;
		}
		else if (strcmp(command, "Probability") == 0)
		{
			std::cout << deck.calcProbability(this->player.getScore(), this->rules) 
				<< std::endl;
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
			std::cout << "Enter a valid one!" << std::endl;
		}
	}

	this->updateBinary();
}

void Game::init()
{
	this->initPlayer();

	std::cout << "You will play as " << this->player.name << "." << std::endl;

	this->initDeck();
	this->initRules();
}

void Game::loadPlayers()
{
	int n = countRecords();
	if (n != 0)
	{
		this->loaded = new Player[n];
		this->playersCount = n;
		std::ifstream ifs;
		ifs.open("players.bin", std::ios::in | std::ios::binary);
		if (!ifs)
		{
			std::cerr << "No players to choose from! Create a new player." << std::endl;
		}
		ifs.seekg(0);
		ifs.read((char*) & *this->loaded, sizeof(Player) * n);
		ifs.close();
	}
}

int Game::countRecords()
{
	int n;
	std::ifstream ifs;
	ifs.open("players.bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		std::cerr << "No players to choose from! Create a new player." << std::endl;
		return 0;
	}
	ifs.seekg(0, std::ios::end);

	n = ifs.tellg() / sizeof(Player);
	ifs.close();
	return n;
}

void Game::printPlayers()
{
	for (int i = 0; i < this->playersCount; i++)
	{
		this->loaded[i].printPlayer(std::cout) << std::endl;
	}
}

void Game::saveBinary()
{
	std::ofstream ofs;
	ofs.open("players.bin", std::ios::out | std::ios::binary);
	if (!ofs)
	{
		std::cerr << "Not able to open binary!" << std::endl;
	}
	ofs.seekp(0, std::ios::beg);
	ofs.write((char*) & *this->loaded, sizeof(Player) * this->playersCount);
	ofs.close();
	std::cout << "All changes are saved successfully in the file!" << std::endl;
}

void Game::updateBinary()
{
	if (this->customPlayerGame)
	{
		Player* temp = new Player[this->playersCount + 1];
		for (int i = 0; i < this->playersCount; i++)
		{
			temp[i] = loaded[i];
		}
		// erase game activity before saving
		this->player.clearActivity();
		temp[this->playersCount] = this->player;
		this->playersCount++;

		delete[] this->loaded;
		this->loaded = new Player[this->playersCount];

		for (int i = 0; i < this->playersCount; i++)
		{
			this->loaded[i] = temp[i];
		}
		delete[] temp;

		saveBinary();
	}
	else
	{
		this->player.clearActivity();
		this->loaded[this->playerIndex] = this->player;
		saveBinary();
	}
}

void Game::initPlayer()
{
	std::cout << "Choose a player or enter a new player:" << std::endl;
	char name[Constants::PlayerMaxNameLen];
	std::cin.getline(name, Constants::PlayerMaxNameLen - 1);

	// check for a player with that name
	for (int i = 0; i < this->playersCount; i++)
	{
		if (strcmp(loaded[i].name, name) == 0)
		{
			this->player = this->loaded[i];
			this->playerIndex = i;
			break;
		}
	}

	if (strcmp(this->player.name, "") == 0)
	{
		// create a new player with that name
		this->player = Player(name);
		this->customPlayerGame = true;
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
			if (!std::cin)
			{
				std::cin.clear();
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (deckSize < 50 || deckSize > 104);

		this->deck = Deck(deckSize, "inputSN");
	}
}

void Game::initRules()
{
	int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 10, 10, 10 };
	this->rules.setPoints(points);
}
