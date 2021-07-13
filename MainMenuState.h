#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState:
	public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void endState();

	void updateInput(const float& dt);
	void updateButtons();
	void Update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr);
};
