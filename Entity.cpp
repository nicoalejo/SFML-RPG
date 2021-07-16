#include "Entity.h"

void Entity::initVariables()
{
	this->sprite = nullptr;
	this->texture = nullptr;

	this->movementComponent = nullptr;
}

Entity::Entity()
{
	this->initVariables();
	
}

Entity::~Entity()
{
	delete this->sprite;
	delete this->movementComponent;
}

//Component functions
void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}

void Entity::createMovementComponent(const float maxVelocity)
{
	this->movementComponent = new MovementComponent(maxVelocity);
}

//Functions

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite) {
		this->sprite->setPosition(x, y);
	}
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->sprite && this->movementComponent) {
		//Sets velocity
		this->movementComponent->move(dir_x, dir_y);
		//Uses velocity
		this->sprite->move(this->movementComponent->getVelocity() * dt);
	}
	
}

void Entity::Update(const float& dt)
{
	
}

void Entity::Render(sf::RenderTarget* target)
{
	if (this->sprite) {
		target->draw(*this->sprite);
	}
}
