#include "Enemy.h"

//Initializer Functions
void Enemy::initVariables()
{
	this->sprite_size = 128;
	this->walkVelocity = 10.f;
	this->attacking = false;	
}

void Enemy::initComponents(sf::Texture& texture_sheet, std::string configFile)
{
	//Create Components
	this->createHitboxComponent(this->sprite, 32.f, 32.f, 64.f, 64.f);
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->createAudioComponent("Resources/Sounds/SFX/sword.ogg");

	std::string healthLine = "";
	int health = 0;
	int attack = 0;
	int points = 0;

	std::ifstream ifs(configFile);
	if (ifs.is_open()) {
		std::getline(ifs, healthLine);
		ifs >> attack;
		ifs >> points;
		health = stoi(healthLine);		
	}
	ifs.close();

	this->createAttributeComponent(health, attack, points);	

}

//Constructors / Destructors
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, Player* player, std::string configFile, std::vector<sf::FloatRect>& unwalkable) :
	player(player), unwalkable(unwalkable)
{
	this->initVariables();
	this->initComponents(texture_sheet, configFile);

	this->setPosition(x, y);


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

Enemy::~Enemy()
{
}


//Functions
void Enemy::checkCollision(sf::Vector2f oldPosition)
{
	for (auto it = this->unwalkable.begin(); it != this->unwalkable.end(); ++it)
	{
		if (this->hitboxComponent->checkIntersect(*it)) {
			this->setPosition(oldPosition.x, oldPosition.y);
		}
	}	
	if (this->hitboxComponent->checkIntersect(player->hitboxComponent->getHitbox().getGlobalBounds())) {
		this->setPosition(oldPosition.x, oldPosition.y);
	}
}

sf::FloatRect Enemy::getFloatRect()
{
	return sf::FloatRect(this->getPosition().x, this->getPosition().y, 64.f, 64.f);
}

void Enemy::isAttacked()
{	
	if (this->player->isAttacking()) {
		this->player->isAttacking() = false;
		float distance = calculateDistancePlayer(this->player->getPosition());
		if (distance < 150.f){
			this->attributeComponent->reduceHealth(this->player->getAttributeComponent()->getAttack());
		}
	}	 
}

void Enemy::updateAttack(const float& dt)
{			
	sf::Vector2f direction = normalize(this->player->getPosition() - this->sprite.getPosition());

	float distance = calculateDistancePlayer(this->player->getPosition());
	if (distance < 300.f && distance > 100.f)
		this->movementComponent->move(direction.x, direction.y, dt);
	else if (distance <= 100.f)
		attacking = true;
	else {
		attacking = false;
	}
}

bool Enemy::checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement,
	const std::string keyAttack)
{
	if (this->animationComponent->checkCurrentAnimation(keyMovement) ||
		this->animationComponent->checkCurrentAnimation(keyAttack)) {
		if (this->animationComponent->play(keyAttack, dt, true)) {
			this->player->getAttributeComponent()->reduceHealth(this->attributeComponent->getAttack());
			this->attacking = false;
		}
		return true;
	}
	return false;
}
void Enemy::attackAnimation(const float& dt)
{
	if (this->attacking) {
		if (!checkAndPlayAttackAnimation(dt, "IDLE", "ATTACK_RIGHT"))
			if (!checkAndPlayAttackAnimation(dt, "WALK_LEFT", "ATTACK_LEFT"))
				if (!checkAndPlayAttackAnimation(dt, "WALK_RIGHT", "ATTACK_RIGHT"))
					if (!checkAndPlayAttackAnimation(dt, "WALK_UP", "ATTACK_UP"))
						checkAndPlayAttackAnimation(dt, "WALK_DOWN", "ATTACK_DOWN");
	}

}

void Enemy::updateAnimation(const float& dt)
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



void Enemy::Update(const float& dt)
{
	sf::Vector2f oldPosition = this->getPosition();

	this->movementComponent->Update(dt);

	this->updateAttack(dt);

	this->isAttacked();

	this->updateAnimation(dt);

	this->hitboxComponent->Update();

	this->checkCollision(oldPosition);
}
