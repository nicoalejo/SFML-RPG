#pragma once
#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
private:
	//Variables
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states);
	virtual ~EditorState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void Update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
};

