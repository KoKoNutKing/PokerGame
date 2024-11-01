#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Deck.h"
#include "Player.h"
#include "Table.h"

//Game engine.
//Wrapper class.

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window; //i will understand it later
	sf::VideoMode videoMode;
	sf::Event event;

	//Mouse position
	sf::Vector2i mousePos;
	//Objects
	std::vector<Player> players;
	Table table;
	Deck deck;

	//private functions
	void initVariables();
	void initWindow();


public:
	//Constructs/ Destructs
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Fun
	void pollEvents();
	void setupPlayers();


	void updateMousePos();
	void update();
	void display();
};

#endif


