#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = IDLE;
	
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(34);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width * 0.5f) - this->text.getGlobalBounds().width * 0.5f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height * 0.5f) - this->text.getGlobalBounds().height * 0.5f
		);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
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
		break;
	case HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
