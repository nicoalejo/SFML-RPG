#pragma once

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;
	
	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

	//Functions

	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};

