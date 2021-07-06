#pragma once

#include "GameState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	//Initializers
	void InitWindow();
	void initStates();

public:
	//Constructors and destructors
	Game();
	virtual ~Game();

	//Functions
	void UpdateDT();
	void UpdateSFMLEvents();
	void Update();
	void Render();
	void Run();
};

