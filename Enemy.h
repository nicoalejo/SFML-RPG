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
        std::vector<sf::FloatRect> unwalkable;
    

        //Initializer Functions
        void initVariables();
        void initComponents(sf::Texture& texture_sheet, std::string configFile);

        void checkCollision(sf::Vector2f oldPosition);

    public:
        Enemy(float x, float y, sf::Texture& texture_sheet, Player* player, std::string configFile, std::vector<sf::FloatRect>& unwalkable);
        virtual ~Enemy();

        //Functions   
        sf::FloatRect getFloatRect();
        void isAttacked();
        void updateAttack(const float& dt);
        bool checkAndPlayAttackAnimation(const float& dt, const std::string keyMovement,
            const std::string keyAttack);
        void attackAnimation(const float& dt);
        void updateAnimation(const float& dt);
        virtual void Update(const float& dt);
    
};
