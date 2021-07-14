#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:
	void initVariables();
protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void createSprite(sf::Texture* texture);

	//Functions

	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};

