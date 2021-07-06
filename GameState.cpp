#include "GameState.h"

GameState::GameState(sf::RenderTarget* window):State(window)
{
	
}

GameState::~GameState()
{
}

void GameState::endState()
{

}

void GameState::Update(const float& dt)
{
	std::cout << "Hellou from GameState" << "\n";
}

void GameState::Render(sf::RenderTarget* target)
{
}
