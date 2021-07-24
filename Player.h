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
    sf::Text healthText;
    sf::Font font;

    //Initializer Functions
    void initVariables();
    void initComponents(sf::Texture& texture_sheet);
    void initUI();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    AttributeComponent* getAttributeComponent();
    
    //Functions   

    void updateUI();
    void updateAttack();
    bool checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement, 
        const std::string keyAttack);
    void attackAnimation(const float& dt);
    void updateAnimation(const float& dt);
    virtual void Update(const float& dt);
    void Render(sf::RenderTarget& target) override;
};

