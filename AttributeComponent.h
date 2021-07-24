#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class AttributeComponent
{
private:
	int maxHP;
	int currentHP;
	int attack;
	int score = 0;
	int points;
	bool dead;

	sf::Text hpText;

public:
	//Constructors
	AttributeComponent(int health, int attack, int points);
	virtual ~AttributeComponent();

	//Accessors
	int getMaxHP();
	int getCurrentHP();
	int getAttack();
	int getScore();
	int getPoints();
	bool isDead();

	//Functions
	void reduceHealth(int damage);
};

