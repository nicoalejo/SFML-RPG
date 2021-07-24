#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int health, int attack, int points)
	: maxHP(health), attack(attack), points(points)
{
	this->currentHP = maxHP;
	this->dead = false;
}


AttributeComponent::~AttributeComponent()
{
}

//Accessors
int AttributeComponent::getMaxHP()
{
	return this->maxHP;
}

int AttributeComponent::getCurrentHP()
{
	return this->currentHP;
}

int AttributeComponent::getAttack()
{
	return this->attack;
}

int AttributeComponent::getScore()
{
	return this->score;
}

int AttributeComponent::getPoints()
{
	return this->points;
}

bool AttributeComponent::isDead()
{
	return this->dead;
}

//Functions
void AttributeComponent::reduceHealth(int damage)
{
	this->currentHP -= damage;
	if (this->currentHP <= 0) {
		this->currentHP = 0;
		this->dead = true;
	}
}
