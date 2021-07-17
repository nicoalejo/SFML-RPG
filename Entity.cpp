#include "Entity.h"

void Entity::initVariables()
{
	this->texture = nullptr;

	this->movementComponent = nullptr;
}

Entity::Entity()
{
	this->initVariables();

}

Entity::~Entity()
{
	delete this->movementComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->texture = &texture;
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity);
}

//Functions

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->movementComponent) {
		//Sets velocity
		this->movementComponent->move(dir_x, dir_y, dt);
	}

}

void Entity::Update(const float& dt)
{

}

void Entity::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
