#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variables
    

    //Initializer Functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
};

