#include<iostream>
#include "Game.h"
#include <fstream>

void Game::start()
{
	bool end = false;
	bool custom_player = false;

	seed_players();

	// TODO: check for players in file

	// for testing purposes
	int n = 3;
	Player* players = new Player[n];

	load_players(players, n);
	print_players(players, n);

	Player currentPlayer;

	std::cout << "Choose a player or enter a new player:" << std::endl;
	char name[99];
	std::cin.getline(name, 100);
	////// check for a player with that name
	for (size_t i = 0; i < n; i++)
	{
		if (strcmp(players[i].name, name) == 0)
		{
			currentPlayer = players[i];
			break;
		}
	}

	if (strcmp(currentPlayer.name, "") == 0)
	{
		// create a new player with that name
		currentPlayer = Player(name);
		custom_player = true;
	}

	// create dealer
	Player dealer;
	std::cout << "You will play as " << currentPlayer.name << "." << std::endl;
	std::cout << "To choose default deck, enter default." << std::endl;
	std::cout << "To choose custom deck, enter custom." << std::endl;

	char deck_type[11];
	std::cin.getline(deck_type, 11);

	Deck deck;

	if (strcmp(deck_type, "default") != 0)
	{
		std::cout << "Choоse the size of the deck:" << std::endl;

		// create deck
		int deckSize = 0;
		std::cin >> deckSize;
		std::cin.ignore();
		deck = Deck(deckSize);
	}

	// create rules
	int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 10, 10, 10 };
	Rules rules;
	rules.setCardPoints(points);

	// start game
	std::cout << "Start!" << std::endl;
	char command[13];

	// engine
	while (!end)
	{
		std::cout << "Hit/Stand/Probability" << std::endl;
		std::cin.getline(command, 12);

		if (strcmp(command, "Hit") == 0)
		{
			// draw a card from the deck
			currentPlayer.add_card(deck.draw(), rules);
			currentPlayer.print_drawn(std::cout);

			if (currentPlayer.get_score() > 21)
			{
				std::cout << "You lose!" << std::endl;
				end = true;
			}
		}
		else if (strcmp(command, "Stand") == 0)
		{
			// start dealer draw
			while (dealer.get_score() <= 17)
			{
				dealer.add_card(deck.draw(), rules);
			}

			dealer.print_drawn(std::cout);

			if (dealer.get_score() > 21)
			{
				std::cout << "You won!" << std::endl;
			}
			else
			{
				// compare scores
				if (currentPlayer.get_score() >= dealer.get_score())
				{
					std::cout << "You won!" << std::endl;
				}
				else
				{
					std::cout << "You lose!" << std::endl;
				}
			}
			end = true;
		}
		else if (strcmp(command, "Probability") == 0)
		{
			std::cout << deck.find_probability(currentPlayer.get_score()) << std::endl;
		}
		else
		{
			std::cerr << "Invalid command!" << std::endl;
			std::cerr << "Enter a valid one!" << std::endl;
			std::cin.getline(command, 12);
		}
	}

	// save players to file
	save_players(players, n);

	delete[] players;
}

void Game::print_players(const Player* players, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		players[i].print_player(std::cout) << std::endl;
	}
}

void Game::save_players(const Player* players, int n)
{
	std::ofstream ofs;
	ofs.open("players.bin", std::ios::out | std::ios::binary);
	if (!ofs)
	{
		std::cerr << "Not able to open binary!" << std::endl;
	}
	ofs.seekp(0, std::ios::beg);
	ofs.write((char*) & *players, sizeof(Player) * n);
	ofs.close();
}

void Game::load_players(Player* players, int n)
{
	std::ifstream ifs;
	ifs.open("players.bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		std::cerr << "Not able to open binary!" << std::endl;
	}
	ifs.seekg(0);
	ifs.read((char*) & *players, sizeof(Player) * n);
	ifs.close();
}

void Game::seed_players()
{
	Player* players = new Player[3];
	players[0] = Player("Ivan Ivanov");
	players[1] = Player("Petar Petrov");
	players[2] = Player("Dimitar Dimitrov");

	save_players(players, 3);

	delete[] players;
}
