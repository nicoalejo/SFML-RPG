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
	this->createAudioComponent("Resources/Sounds/SFX/sword.ogg");

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
		if (this->audioComponent->getSound().getStatus() == audioComponent->getSound().Stopped)
			this->audioComponent->playSound();
	}
}

bool Player::checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement,
	const std::string keyAttack)
{	
	if (this->animationComponent->checkCurrentAnimation(keyMovement) ||
		this->animationComponent->checkCurrentAnimation(keyAttack)) {
		if (this->animationComponent->play(keyAttack, dt, true)) {
			this->attacking = false;			
		}			
		return true;
	}
	return false;
}
void Player::attackAnimation(const float& dt)
{
	if (this->attacking) {
		if (!checkAndPlayAttackAnimation(dt, "IDLE", "ATTACK_RIGHT"))
			if (!checkAndPlayAttackAnimation(dt, "WALK_LEFT", "ATTACK_LEFT"))
				if (!checkAndPlayAttackAnimation(dt, "WALK_RIGHT", "ATTACK_RIGHT"))
					if (!checkAndPlayAttackAnimation(dt, "WALK_UP", "ATTACK_UP"))
						checkAndPlayAttackAnimation(dt, "WALK_DOWN", "ATTACK_DOWN");	
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
