#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variables
    int sprite_size;
    float walkVelocity;
    bool attacking;

    //Initializer Functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions   
    void updateAttack();
    bool checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement, 
        const std::string keyAttack);
    void attackAnimation(const float& dt);
    void updateAnimation(const float& dt);
    virtual void Update(const float& dt);
};

