#include "MapGenerator.h"
#include <vector>

//Constructors
MapGenerator::MapGenerator()
{
    this->height = 0;
    this->width = 0;
}

MapGenerator::~MapGenerator()
{
}

//Functions
bool MapGenerator::load(const std::string& tileset, sf::Vector2u tileSize,
    const int* tiles, int width, int height, std::vector<sf::FloatRect>& unwalkable)
{
    this->height = height;
    this->width = width;
    

    if (!m_tileset.loadFromFile(tileset))
        return false;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (tiles[(i * width) + j]) {
            case 0:
                this->setTexture(m_tileset, map_sprite[(width * i) + j], sf::IntRect(128, 0, tileSize.x, tileSize.y));
                this->setPosition(i * tileSize.x, j * tileSize.y, map_sprite[(width * i) + j]);
                break;
            case 1:
                this->setTexture(m_tileset, map_sprite[(width * i) + j], sf::IntRect(256, 0, tileSize.x, tileSize.y));
                this->setPosition(i * tileSize.x, j * tileSize.y, map_sprite[(width * i) + j]);
                unwalkable.push_back(map_sprite[(width * i) + j].getGlobalBounds());
                break;
            case 2:
                this->setTexture(m_tileset, map_sprite[(i * width) + j], sf::IntRect(0, 0, tileSize.x, tileSize.y));
                this->setPosition(i * tileSize.x, j * tileSize.y, map_sprite[(i * width) + j]);
                break;

            }
        }
    }
    return true;
}
void MapGenerator::setTexture(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect rectDimension)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(rectDimension);
}

void MapGenerator::setPosition(const int y, const int x, sf::Sprite& sprite)
{
    sprite.setPosition(x, y);
}

void MapGenerator::Render(sf::RenderTarget& target)
{
    for (int i = 0; i < width*height; i++)
    {
        target.draw(map_sprite[i]);
    }
}

    

