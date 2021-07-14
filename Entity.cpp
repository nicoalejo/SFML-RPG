#include "Entity.h"

void Entity::initVariables()
{
	this->sprite = nullptr;
	this->texture = nullptr;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	this->initVariables();
	
}

Entity::~Entity()
{
	delete this->sprite;
}

//Component functions
void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

//Functions
void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->sprite) {
		this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
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
