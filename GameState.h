#pragma once
#include "State.h"

class GameState : public State
{
private:
	Player* player;

	//Initializer Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

