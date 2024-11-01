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
	this->deck.printDeck();

	
}
//Objects


//Con/destrusctor
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
//Something about game setup
void Game::setupPlayers()
{
	Player pl1("KoKoNut01");
	Player pl2("KoKoNut02");
	table.addPlayer(pl1);
	table.addPlayer(pl2);



}

void Game::updateMousePos()
{
	//relative to window
	this->mousePos = sf::Mouse::getPosition(*this->window);

}

void Game::update()
{
	this->pollEvents();
	//update mouse pos
	this->updateMousePos();
}

void Game::display()
{
	this->window->clear();
	//draw game objects here
	this->table.drawTable(*this->window);
	this->window->display();
}