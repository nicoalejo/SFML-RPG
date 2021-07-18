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
	
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 3, 0, 192, 192);
}

Player::~Player()
{
}

//Functions
void Player::Update(const float& dt)
{
	this->movementComponent->Update(dt);

	this->animationComponent->play("IDLE_LEFT", dt);
}
