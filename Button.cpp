#include "Button.h"

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = IDLE;
	
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width * 0.5f) - this->text.getGlobalBounds().width * 0.5f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height * 0.5f) - this->text.getGlobalBounds().height * 0.5f
		);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	
}

Button::~Button()
{
}

//Accesors
const bool Button::isPressed() const
{
	if(this->buttonState == ACTIVE)
		return true;

	return false;
}


//Functions

void Button::Update(const sf::Vector2f mousePos)
{
	//Update the booleans for hover and active

	//Idle
	this->buttonState = IDLE;
	
	//Hover	
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = HOVER;

		//Active - pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
