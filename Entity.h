#pragma once

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Texture* texture;
	sf::Sprite sprite;
	
	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity);

	//Functions

	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};

