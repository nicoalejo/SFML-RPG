#include "State.h"

int State::gameover = 0;
HighscoreManager* State::HSM = new HighscoreManager(3);

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;	
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}

void State::Render(sf::RenderTarget* target)
{
}
