#pragma once

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::vector<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initializers
	void initVariables();
	void InitWindow();
	void initStates();
	void initKeys();

public:
	//Constructors and destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void UpdateDT();
	void UpdateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};

