#pragma once
#include "Entity.h"
#include <list>

class Player :
    public Entity
{
private:
    //Variables
    int sprite_size;
    float walkVelocity;

    bool attacking;
    bool oneAttack;

    sf::Text healthText;
    sf::Font font;
    
    int score;
    std::vector<sf::FloatRect> unwalkable;
    sf::Vector2f oldPosition;

    //Initializer Functions
    void initVariables();
    void initComponents(sf::Texture& texture_sheet);
    void initUI();

    void checkCollision();

public:
    Player(float x, float y, sf::Texture& texture_sheet, std::vector<sf::FloatRect>& unwalkable);
    virtual ~Player();
    
    //Accesors
    bool& isAttacking();
    void setScore(const int addScore);
    int& getScore();

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

