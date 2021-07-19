#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum button_states {
	IDLE = 0,	
	HOVER,
	ACTIVE,
};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	
	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, sf::Font* font,
		std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
	~Button();

	//Accesors
	const bool isPressed() const;

	//Functions
	void Update(const sf::Vector2f mousePos);
	void Render(sf::RenderTarget& target);
};

