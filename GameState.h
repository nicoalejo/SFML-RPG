#pragma once
#include "State.h"

class GameState : public State
{
private:
	Entity player;
public:
	GameState(sf::RenderTarget* window);
	virtual ~GameState();

	//Functions
	void endState();

	void updateKeyBinds(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

