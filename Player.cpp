#include "Player.h"

//Initializer Functions
void Player::initVariables()
{
	this->sprite_size = 128;
	this->walkVelocity = 10.f;
	this->attacking = false;
	this->oneAttack = false;
	this->score = 0;
}

void Player::initComponents(sf::Texture& texture_sheet)
{
	//Create Components
	this->createHitboxComponent(this->sprite,32.f,32.f, 64.f, 64.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->createAudioComponent("Resources/Sounds/SFX/sword.ogg");

	std::string healthLine = "";
	int health = 0;
	int attack = 0;
	int points = 0;

	std::ifstream ifs("Config/attributes_player.ini");
	if (ifs.is_open()) {
		std::getline(ifs, healthLine);
		ifs >> attack;
		ifs >> points;
		health = stoi(healthLine);		
	}	
	ifs.close();

	this->createAttributeComponent(health, attack, points);

}

void Player::initUI()
{
	if (!this->font.loadFromFile("Fonts/Enchanted-Land.otf")) {
		throw("ERROR::MAINMENUSTATE::Could not load font");
	}

	this->healthText.setFont(this->font);
	this->healthText.setString("HP: " + std::to_string(attributeComponent->getCurrentHP())
		+ "/" + std::to_string(attributeComponent->getMaxHP()));
	this->healthText.setFillColor(sf::Color::Green);
	this->healthText.setCharacterSize(50);
	this->healthText.setPosition(10, 1015);	 
}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet, std::vector<sf::FloatRect>& unwalkable)
	:unwalkable(unwalkable)
{
	this->initVariables();	
	this->initComponents(texture_sheet);
	this->initUI();

	this->setPosition(x, y);

	//Movement Animations
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 3, 0, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_RIGHT", walkVelocity, 0, 5, 7, 5, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_LEFT", walkVelocity, 0, 6, 7, 6, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_DOWN", walkVelocity, 0, 3, 7, 3, sprite_size, sprite_size);
	this->animationComponent->addAnimation("WALK_UP", walkVelocity, 0, 1, 7, 1, sprite_size, sprite_size);

	//Attack Animations
	/*Check for last movement animation to display the right attack*/
	this->animationComponent->addAnimation("ATTACK_RIGHT", 10.f, 0, 12, 7, 12, sprite_size, sprite_size);
	this->animationComponent->addAnimation("ATTACK_LEFT", 10.f, 0, 13, 7, 13, sprite_size, sprite_size);
	this->animationComponent->addAnimation("ATTACK_DOWN", 10.f, 0, 10, 7, 10, sprite_size, sprite_size);
	this->animationComponent->addAnimation("ATTACK_UP", 10.f, 0, 15, 7, 15, sprite_size, sprite_size);
}

bool& Player::isAttacking()
{
	return this->oneAttack;
}

//PRIVATE FUNCTIONS
void Player::checkCollision(sf::Vector2f oldPosition)
{

	for (auto it = this->unwalkable.begin(); it != this->unwalkable.end(); ++it)
	{
		if (this->hitboxComponent->checkIntersect(*it)) {
			this->setPosition(oldPosition.x, oldPosition.y);
		}
	}
}

//PUBLIC FUNCTIONS

void Player::setScore(const int addScore)
{
	this->score += addScore;
}
int& Player::getScore() {
	return this->score;
}

Player::~Player()
{
}

//Functions

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->attacking = true;			
		if (this->audioComponent->getSound().getStatus() == this->audioComponent->getSound().Stopped)
			this->audioComponent->playSound();
		
	}
}

bool Player::checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement,
	const std::string keyAttack)
{	
	if (this->animationComponent->checkCurrentAnimation(keyMovement) ||
		this->animationComponent->checkCurrentAnimation(keyAttack)) {
		if (this->animationComponent->play(keyAttack, dt, true)) {
			this->oneAttack = true;
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

void Player::updateUI() 
{
	this->healthText.setString("HP: " + std::to_string(attributeComponent->getCurrentHP())
		+ "/" + std::to_string(attributeComponent->getMaxHP()));
}

void Player::Update(const float& dt)
{		
	sf::Vector2f oldPosition = this->getPosition();

	this->movementComponent->Update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->Update();

	this->updateUI();

	checkCollision(oldPosition);

}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->healthText);

	if (this->hitboxComponent) {
		this->hitboxComponent->Render(target);
	}
}