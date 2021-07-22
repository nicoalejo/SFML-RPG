#include "Player.h"

//Initializer Functions
void Player::initVariables()
{
	this->sprite_size = 128;
	this->walkVelocity = 10.f;
	this->attacking = false;
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

	//Movement Animations
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 3, 0, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_RIGHT", walkVelocity, 0, 5, 3, 5, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_LEFT", walkVelocity, 0, 6, 3, 6, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_DOWN", walkVelocity, 0, 3, 3, 3, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_UP", walkVelocity, 0, 1, 3, 1, sprite_size, sprite_size);

	//Attack Animations
	/*Check for last movement animation to display the right attack*/
	this->animationComponent->addAnimation("ATTACK_RIGHT", 10.f, 0, 12, 4, 12, sprite_size, sprite_size);
	this->animationComponent->addAnimation("ATTACK_LEFT", 10.f, 0, 13, 4, 13, sprite_size, sprite_size);
	this->animationComponent->addAnimation("ATTACK_DOWN", 10.f, 0, 10, 4, 10, sprite_size, sprite_size);
	this->animationComponent->addAnimation("ATTACK_UP", 10.f, 0, 15, 4, 15, sprite_size, sprite_size);
}

Player::~Player()
{
}

//Functions

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->attacking = true;
	}
}

void Player::attackAnimation(const float& dt)
{
	if (this->attacking) {
		if (this->animationComponent->checkCurrentAnimation("IDLE") ||
			this->animationComponent->checkCurrentAnimation("ATTACK_RIGHT")) {
			if (this->animationComponent->play("ATTACK_RIGHT", dt, true))
				this->attacking = false;
		}
		else if (this->animationComponent->checkCurrentAnimation("WALK_LEFT") ||
			this->animationComponent->checkCurrentAnimation("ATTACK_LEFT")) {
			if (this->animationComponent->play("ATTACK_LEFT", dt, true))
				this->attacking = false;
		}
		else if (this->animationComponent->checkCurrentAnimation("WALK_RIGHT") || 
			this->animationComponent->checkCurrentAnimation("ATTACK_RIGHT")) {
			if (this->animationComponent->play("ATTACK_RIGHT", dt, true))
			this->attacking = false;
		}
		else if (this->animationComponent->checkCurrentAnimation("WALK_UP") ||
			this->animationComponent->checkCurrentAnimation("ATTACK_UP")) {
			if (this->animationComponent->play("ATTACK_UP", dt, true))
				this->attacking = false;
		}
		else if (this->animationComponent->checkCurrentAnimation("WALK_DOWN") ||
			this->animationComponent->checkCurrentAnimation("ATTACK_DOWN")) {
			if (this->animationComponent->play("ATTACK_DOWN", dt, true))
				this->attacking = false;
		}
		/*else {
			this->attacking = false;
		}*/					
	}

}

void Player::updateAnimation(const float& dt)
{
	this->attackAnimation(dt);

	if (this->movementComponent->getState(NOT_MOVING))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_LEFT))
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_DOWN))
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_UP))
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

}

void Player::Update(const float& dt)
{
	this->movementComponent->Update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->Update();
}
