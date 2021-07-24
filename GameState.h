#pragma once
#include "State.h"
#include "MapGenerator.h"
#include <list>

class GameState : public State
{
private:	
	Player* player;
	MapGenerator* newMap;
	//Enemy* enemy;
	std::list<Enemy*> enemies;

	//Initializer Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initMap();
	void initEnemies();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

