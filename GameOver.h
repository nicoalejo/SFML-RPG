#pragma once
#include "State.h"
#include "MainMenuState.h"

class GameOver :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	//Functions
	void initBackground();
	void initKeybinds();	

public:
	GameOver(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameOver();

	//Functions

	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};

