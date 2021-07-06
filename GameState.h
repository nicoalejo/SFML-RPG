#pragma once
#include "State.h"

class GameState : public State
{
private:

public:
	GameState(sf::RenderTarget* window);
	virtual ~GameState();

	//Functions
	void endState();

	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

