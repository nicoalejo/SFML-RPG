#include "GameOver.h"

//Initializar Functions
void GameOver::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (gameover == 1) {
		if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/gameover_bad.jpg")) {
			throw "ERROR::MAIN MENU STATE::FAILED TO LOAD BACKGROUND TEXTURE";
		}
	}		
	else if (gameover == 2){
		if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/gameover_good.jpg")) {
			throw "ERROR::MAIN MENU STATE::FAILED TO LOAD BACKGROUND TEXTURE";
		}
	}
	this->background.setTexture(&this->backgroundTexture);
}

void GameOver::initKeybinds()
{
	std::ifstream ifs("Config/gameover_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();

}

GameOver::GameOver(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initBackground();
	this->initKeybinds();
}

GameOver::~GameOver()
{

}

void GameOver::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		gameover = 0;
		this->endState();
	}
		
}

void GameOver::Update(const float& dt)
{
	this->updateInput(dt);
}

void GameOver::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
}