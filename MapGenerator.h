#pragma once
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MapGenerator
{
private:
	sf::Texture m_tileset;
	sf::Sprite map_sprite[150];
	int width;
	int height;

public:
	//Constructors
	MapGenerator();
	virtual ~MapGenerator();

	//Functions
	bool load(const std::string& tileset, sf::Vector2u tileSize,
		const int* tiles, int width, int height);
	void setPosition(const int x, const int y, sf::Sprite& sprite);
	void setTexture(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect rectDimension);

	void Render(sf::RenderTarget& target);
};


