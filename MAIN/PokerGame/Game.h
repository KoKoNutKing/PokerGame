#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

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
	void update();
	void display();
};

#endif


