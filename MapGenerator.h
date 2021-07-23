#pragma once
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MapGenerator
{
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

public:
	//Constructors
	MapGenerator();
	virtual ~MapGenerator();

	//Functions
	bool load(const std::string& tileset, sf::Vector2u tileSize,
		const int* tiles, unsigned int width, unsigned int height);

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};


