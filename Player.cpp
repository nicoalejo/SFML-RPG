#include "Player.h"

//Initializer Functions
void Player::initVariables()
{
}

void Player::initComponents()
{


}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();	
	
	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(this->sprite, texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 1, 1, 14, 1, 192, 192);
}

Player::~Player()
{
}
