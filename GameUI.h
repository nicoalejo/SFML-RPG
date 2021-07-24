#pragma once
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameUI
{
private:	
	std::map<std::string, sf::Text> UIText;
public:
	GameUI();
	virtual ~GameUI();

};

