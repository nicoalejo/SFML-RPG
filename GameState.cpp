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
	this->player = new Player(100,100, this->textures["PLAYER_SHEET"], unwalkable);
}

void GameState::initMap()
{
	this->newMap = new MapGenerator();
	const int level[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 
		1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 
		0, 1, 0, 0, 2, 0, 2, 2, 2, 0, 1, 1, 1, 0, 0, 
		0, 1, 1, 0, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 0, 
		0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 
		2, 0, 1, 0, 2, 0, 0, 0, 2, 0, 1, 1, 1, 1, 1, 
		0, 0, 1, 0, 2, 2, 0, 2, 0, 0, 0, 0, 1, 1, 1, 
	};
	
	if (!this->newMap->load("Resources/Images/map/tiles_128.png", sf::Vector2u(128, 128), level, 15, 8,unwalkable))
		throw "ERROR_MAPGENERATOR::UNABLE_TO_LOAD_MAP";
}

void GameState::initEnemies()
{
	this->enemies.push_back(new Enemy(1024, 500, this->textures["ENEMY_SHEET"], player, std::string("Config/attributes_enemy.ini"),unwalkable));
	this->enemies.push_back(new Enemy(1024, 700, this->textures["ENEMY_SHEET"], player, std::string("Config/attributes_enemy.ini"),unwalkable));
}

void GameState::initUI()
{
	if (!this->font.loadFromFile("Fonts/Enchanted-Land.otf")) {
		throw("ERROR::MAINMENUSTATE::Could not load font");
	}

	this->highscoreText.setFont(this->font);
	this->highscoreText.setString("HighScore: " + std::to_string(HSM->GetScore(1)->GetScore()));		
	this->highscoreText.setFillColor(sf::Color::Cyan);
	this->highscoreText.setCharacterSize(50);
	this->highscoreText.setPosition(900, 1015);

	this->currentscoreText.setFont(this->font);
	this->currentscoreText.setString("Current Score: " + std::to_string(player->getScore()));
	this->currentscoreText.setFillColor(sf::Color::Red);
	this->currentscoreText.setCharacterSize(50);
	this->currentscoreText.setPosition(1500, 1015);
}

//Constructor / Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initMap();
	this->initPlayers();
	this->initEnemies();
	this->initUI();

	std::cout << HSM->GetScore(1)->GetScore();
}

GameState::~GameState()
{
	delete this->player;
	delete this->newMap;
	for (auto enemy : enemies)
	{
		delete enemy;
	}	
}

//Functions

void GameState::checkCollisionPlayer()
{
//get hitbox position and not enemy
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{				
		if (this->player->hitboxComponent->checkIntersect(
			(*it)->hitboxComponent->getHitbox().getGlobalBounds())) {
			this->player->setPosition(oldposition.x, oldposition.y);
		}
	}
}

void GameState::updateCurrentScore()
{
	this->currentscoreText.setString("Current Score: " + std::to_string(player->getScore()));
}

void GameState::updateHighScore()
{
	if (this->HSM->GetScore(1) == NULL || this->HSM->GetScore(1)->GetScore() < player->getScore())
		this->HSM->AddScore("AAA", player->getScore());
}

void GameState::updateEnemies(const float& dt)
{
	for (auto it = this->enemies.begin(); it != this->enemies.end();)
	{
		if ((*it)->getAttributeComponent()->isDead()) {
			this->player->setScore((*it)->getAttributeComponent()->getPoints());
			it = this->enemies.erase(it);			
		}
		else {
			++it;
		}
	}
	if (!enemies.empty())
		for (auto enemy : this->enemies)
		{
			enemy->Update(dt);
		}
	else {
		gameover = 2;
		states->push_back(new GameOver(this->window, this->supportedKeys, this->states));
		updateHighScore();
		this->endState();
	}
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
	if (player->getAttributeComponent()->isDead()) {
		gameover = 1;
		updateHighScore();	
		states->push_back(new GameOver(this->window, this->supportedKeys, this->states));
	}		
	else {
		
		this->oldposition = player->getPosition();

		this->updateMousePosition();
		this->updateInput(dt);
		this->player->Update(dt);
		this->updateEnemies(dt);
		this->updateCurrentScore();

		this->checkCollisionPlayer();
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->newMap->Render(*target);

	target->draw(this->highscoreText);
	target->draw(this->currentscoreText);

	this->player->Render(*target);
	
	for (auto enemy : enemies)
	{
		enemy->Render(*target);
	}
}
