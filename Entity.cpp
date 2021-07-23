#include "Entity.h"

void Entity::initVariables()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}

Entity::Entity()
{
	this->initVariables();

}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
	delete this->audioComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitBoxComponent(this->sprite, offset_x, offset_y, width, height);
}
void Entity::createAudioComponent(const std::string& audio_location)
{
	this->audioComponent = new AudioComponent(audio_location);
}
//Functions

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent) {
		//Sets velocity
		this->movementComponent->move(dir_x, dir_y, dt);
	}

}

void Entity::Update(const float& dt)
{

}

void Entity::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->Render(target);
	}
}
