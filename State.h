#pragma once

#include "Entity.h"

class State
{
private:

protected:
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

