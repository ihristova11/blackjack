#include <iostream>
#include <fstream>

#include "CardType.h"
#include "Player.h"
#include "Deck.h"
#include "Rules.h"

void loadPlayers(Player* players, int n)
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

void seedPlayers()
{
	Player* players = new Player[3];
	players[0] = Player("Ivan Ivanov");
	players[1] = Player("Petar Petrov");
	players[2] = Player("Dimitar Dimitrov");

	std::ofstream ofs;
	ofs.open("players.bin", std::ios::out | std::ios::binary);
	if (!ofs)
	{
		std::cerr << "Not able to open binary!" << std::endl;
	}
	ofs.seekp(0, std::ios::beg);
	ofs.write((char*) & *players, sizeof(Player) * 3);
	ofs.close();
}

int main()
{
	bool end = false;

	seedPlayers();

	// TODO: check for players in file

	// for testing purposes
	int n = 3; 
	Player* players = new Player[n]; // to be deleted
	loadPlayers(players, n);

	Player currentPlayer;

	std::cout << "Chose a player or enter a new player:" << std::endl;
	char name[99];
	std::cin.getline(name, 100);
	////// check for a player with that name
	for (size_t i = 0; i < n; i++)
	{
		if (strcmp(players[i].name, name))
		{
			currentPlayer = players[i];
		}
	}

	if (currentPlayer.name == nullptr)
	{
		// create a new player with that name
		currentPlayer.name = name;
	}

	// create dealer
	Player dealer(); // default player

	// print message for success
	std::cout << "You will play as " << currentPlayer.name << ". Choоse the size of the deck:" << std::endl;
	int deckSize = 0;
	std::cin >> deckSize;
	Deck deck(deckSize);
	
	// for testing purposes since there is no information in the assignment
	int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 10, 10, 10 };
	Rules rules;
	rules.setCardPoints(points);

	std::cout << "Start!" << std::endl;

	// engine
	while (!end)
	{
		std::cout << "Hit/Stand/Probability" << std::endl;
		char command[12];
		std::cin.getline(command, 11);

		if (strcmp(command, "Hit"))
		{
			// draw a card from the deck
			deck.draw();
			// update player's score

		}
		else if (strcmp(command, "Stand"))
		{

		}
		else if (strcmp(command, "Probability"))
		{

		}
		else
		{
			std::cerr << "Invalid command!" << std::endl;
			std::cerr << "Enter a valid one!" << std::endl;
			std::cin.getline(command, 11);
		}
	}

	// save players to file

	delete[] players;

	return 0;
}