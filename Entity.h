#pragma once

#include "AttributeComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"
#include "AudioComponent.h"

class Entity
{
private:
	void initVariables();
protected:
		

public:
	sf::Sprite sprite;

	HitBoxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AudioComponent* audioComponent;
	AttributeComponent* attributeComponent;

	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, 
		float width, float height);
	void createAudioComponent(const std::string& audio_location);
	void createAttributeComponent(const int health, const int attack, const int points);

	//Functions

	AttributeComponent* getAttributeComponent();
	float calculateDistancePlayer(const sf::Vector2f& source);
	sf::Vector2f normalize(const sf::Vector2f& source);
	virtual sf::Vector2f getPosition();
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget& target);
};

