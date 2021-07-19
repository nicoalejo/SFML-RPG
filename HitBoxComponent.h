#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class HitBoxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, 
		float width, float height);
	virtual ~HitBoxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void Update();
	void Render(sf::RenderTarget& target);
};

