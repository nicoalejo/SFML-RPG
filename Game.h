#pragma once

#include "State.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	//Initializers
	void InitWindow();

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

