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

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

	//Init Functions

public:
	//Constructor Destructor
	MovementComponent(sf::Sprite& sprite, float maxVelocity);
	virtual ~MovementComponent();

	//Accesors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float dirX, const float dirY, const float& dt);
	void update(const float& dt);
};

