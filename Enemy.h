#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy :
    public Entity
{
    private:
        //Variables
        int sprite_size;
        float walkVelocity;
        bool attacking;
        Player* player;

        //Initializer Functions
        void initVariables();
        void initComponents();

    public:
        Enemy(float x, float y, sf::Texture& texture_sheet, Player* player);
        virtual ~Enemy();

        //Functions   
        float calculateDistancePlayer();
        sf::Vector2f normalize(const sf::Vector2f& source);
        void updateAttack(const float& dt);
        bool checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement,
            const std::string keyAttack);
        void attackAnimation(const float& dt);
        void updateAnimation(const float& dt);
        virtual void Update(const float& dt);
    
};
