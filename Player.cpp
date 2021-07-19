#include "Player.h"

//Initializer Functions
void Player::initVariables()
{
	sprite_size = 128;
}

void Player::initComponents()
{


}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();	
	
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite,32.f,32.f, 64.f, 64.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 3, 0, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 5, 3, 5, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 6, 3, 6, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 3, 3, 3, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 1, 3, 1, sprite_size, sprite_size);
}

Player::~Player()
{
}

//Functions
void Player::Update(const float& dt)
{
	this->movementComponent->Update(dt);

	if(this->movementComponent->getState(NOT_MOVING))
		this->animationComponent->play("IDLE_DOWN", dt);
	else if(this->movementComponent->getState(MOVING_LEFT))
		this->animationComponent->play("WALK_LEFT", dt);
	else if (this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("WALK_RIGHT", dt);
	else if (this->movementComponent->getState(MOVING_DOWN))
		this->animationComponent->play("WALK_DOWN", dt);
	else if (this->movementComponent->getState(MOVING_UP))
		this->animationComponent->play("WALK_UP", dt);


	this->hitboxComponent->Update();
}
