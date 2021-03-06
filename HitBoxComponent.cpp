#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y,
	float width, float height) 
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
}

HitBoxComponent::~HitBoxComponent()
{
}

sf::RectangleShape HitBoxComponent::getHitbox()
{
	return hitbox;
}

//Functions
bool HitBoxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return (this->hitbox.getGlobalBounds().intersects(frect));
}

void HitBoxComponent::Update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitBoxComponent::Render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
