#include "MovementComponent.h"

//Constructor Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
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
	//Acceleration of the sprite 
	
	this->velocity.x += this->acceleration * dirX;

	this->velocity.y += this->acceleration * dirY;	
}

void MovementComponent::Update(const float& dt)
{
	//Decelerates the sprite checking if has reached max velocity
	
	//Deceleration X
	if (this->velocity.x > 0.f) {

		//Max Velocity check positive
		if(this->velocity.x > this->maxVelocity) //right movement
			this->velocity.x = this->maxVelocity;

		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0;
	}
	else if (this->velocity.x < 0.f) {
		//Max Velocity check negative
		if (this->velocity.x < -this->maxVelocity) //left movement
			this->velocity.x = -this->maxVelocity;

		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0;
	}

	//Deceleration Y
	if (this->velocity.y > 0.f) {

		//Max Velocity check downwards
		if (this->velocity.y > this->maxVelocity) //down movement
			this->velocity.y = this->maxVelocity;

		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0;
	}
	else if (this->velocity.y < 0.f) {
		//Max Velocity check upwards
		if (this->velocity.y < -this->maxVelocity) //up movement
			this->velocity.y = -this->maxVelocity;

		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0;
	}

	//Final Move
	this->sprite.move(this->velocity * dt);
}
