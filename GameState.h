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
	std::vector<sf::FloatRect> unwalkable;
	sf::Vector2f oldposition;
	std::vector<Enemy*> enemies;
	std::vector<sf::Vector2f> enemiesOldPositions;

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
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states);
	virtual ~GameState();
	
	//Functions

	void updateOldPositions();
	void checkCollisionPlayer();
	void checkCollisionBetweenEnemies();
	void updateCurrentScore();
	void updateHighScore();
	void updateEnemies(const float& dt);
	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

