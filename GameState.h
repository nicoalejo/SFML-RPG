#pragma once
#include "State.h"
#include "MapGenerator.h"
#include "GameOver.h"
#include <list>

class GameState : public State
{
private:	
	Player* player;
	MapGenerator* newMap;
	std::list<Enemy*> enemies;

	sf::Text highscoreText;
	sf::Text currentscoreText;
	sf::Font font;

	//Initializer Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initMap();
	void initEnemies();
	void initUI();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();
	
	//Functions

	void updateCurrentScore();
	void updateHighScore();
	void updateEnemies(const float& dt);
	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

