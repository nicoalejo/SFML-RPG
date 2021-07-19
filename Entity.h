#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;
	
	HitBoxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, 
		float width, float height);

	//Functions

	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget& target);
};

