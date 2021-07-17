#include "MovementComponent.h"

//Constructor Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity)
	: sprite(sprite), maxVelocity(maxVelocity)
{

}

MovementComponent::~MovementComponent()
{
}

//Accesors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Functions
void MovementComponent::move(const float dirX, const float dirY, const float& dt)
{
	this->velocity.x = this->maxVelocity * dirX;
	this->velocity.y = this->maxVelocity * dirY;

	this->sprite.move(this->velocity * dt);
}

void MovementComponent::update(const float& dt)
{
}
