#pragma once

#include<vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:
	sf::RenderTarget* window;
	std::vector<sf::Texture> textures;
	bool quit;

public:
	State(sf::RenderTarget* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateKeyBinds(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};

