#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Button.h"

class MainMenuState:
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Music backgroundMusic;

	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initMusic();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	
	void playMusic();
	void updateInput(const float& dt);
	void updateButtons();
	void Update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
};

