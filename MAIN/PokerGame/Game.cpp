#include "Game.h"


//Private Fun
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Poker", sf::Style::Default);
	
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{

}
//Acessor
const bool Game::running() const
{
	return this->window->isOpen();
}



//Funtions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::display()
{
	this->window->clear(sf::Color(0, 0, 0, 0));

	this->window->display();
}