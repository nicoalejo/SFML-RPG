#include "GameState.h"

GameState::GameState(sf::RenderTarget* window):State(window)
{
	
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending Game State!" << "\n";
}

void GameState::updateKeyBinds(const float& dt)
{
	this->checkForQuit();
}

void GameState::Update(const float& dt)
{
	this->updateKeyBinds(dt);
	this->player.Update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (target) {

	}
	else {
		this->player.Render(this->window);
	}	
}
