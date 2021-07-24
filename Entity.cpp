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
	delete this->attributeComponent;
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
void Entity::createAttributeComponent(const int health, const int attack, const int points)
{
	this->attributeComponent = new AttributeComponent(health, attack, points);
}
//Functions

AttributeComponent* Entity::getAttributeComponent()
{
	return attributeComponent;
}

float Entity::calculateDistancePlayer(const sf::Vector2f& source)
{
	float distx = source.x - sprite.getPosition().x;
	float disty = source.y - sprite.getPosition().y;

	return sqrt((distx * distx) + (disty * disty));
}

sf::Vector2f Entity::normalize(const sf::Vector2f& source)
{
	float distance = sqrt((source.x * source.x) + (source.y * source.y));
	if (distance != 0)
		return sf::Vector2f(source.x / distance, source.y / distance);
	else
		return source;
}

sf::Vector2f Entity::getPosition()
{	
	return sprite.getPosition();
}

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
