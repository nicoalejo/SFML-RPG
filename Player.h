#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variables
    int sprite_size;

    //Initializer Functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    virtual void Update(const float& dt);
};

