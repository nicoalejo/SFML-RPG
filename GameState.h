#pragma once
#include "State.h"

class GameState : public State
{
private:
	Entity player;

	//Functions
	void initKeybinds();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	//Functions
	void endState();

	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

