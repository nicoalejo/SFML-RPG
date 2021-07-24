#include "GameState.h"

//Initializer Functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();

}

void GameState::initTextures()
{		
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/necromancer_spritesheet.png")) {
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER TEXTURE";
	}
	if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Images/Sprites/Player/enemy_walk_128_3.png")) {
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER TEXTURE";
	}
}

void GameState::initPlayers()
{
	//Send position x,y and texture
	this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
}

void GameState::initMap()
{
	this->newMap = new MapGenerator();
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 
		1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 
		0, 1, 0, 0, 2, 0, 2, 2, 2, 0, 1, 1, 1, 0, 0, 
		0, 1, 1, 0, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 0, 
		0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 
		2, 0, 1, 0, 2, 0, 0, 0, 2, 0, 1, 1, 1, 1, 1, 
		0, 0, 1, 0, 2, 2, 0, 2, 0, 0, 0, 0, 1, 1, 1, 
	};
	
	if (!this->newMap->load("Resources/Images/map/tiles_128.png", sf::Vector2u(128, 128), level, 15, 8))
		throw "ERROR_MAPGENERATOR::UNABLE_TO_LOAD_MAP";
}

void GameState::initEnemies()
{
	this->enemy = new Enemy(1024, 500, this->textures["ENEMY_SHEET"], player);
}

//Constructor / Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initMap();
	this->initPlayers();
	this->initEnemies();
}

GameState::~GameState()
{
	delete this->player;
	delete this->newMap;
	delete this->enemy;
}

void GameState::updateInput(const float& dt)
{
	//Player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::Update(const float& dt)
{
	if (player->getAttributeComponent()->isDead())
		std::cout << "Muerto" << "\n";

	this->updateMousePosition();
	this->updateInput(dt);
	this->player->Update(dt);
	this->enemy->Update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->newMap->Render(*target);

	this->player->Render(*target);
	
	this->enemy->Render(*target);
}
