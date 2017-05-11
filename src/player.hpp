#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "item.hpp"
#include <math.h>

class Player
{
    public:
        Player();
        
        sf::Vector2i const& getPosition();
        sf::Sprite& getSprite();
        Item const& getInventory();
        bool isMoving();

        void move(int, int);
        void animate();
        Item swapInventory(Item);
        void setSprites();

    private:

        sf::Vector2i _pos;
        unsigned _age;
        unsigned _ageStep = 0;
        unsigned _faceDirection = 0;
        int _frame = -10;
        bool _moveAnimation = false;
        sf::Vector2f _originalPos;
        
        std::vector<sf::Sprite> _sprites;
        std::vector<sf::Texture> _textures;

        sf::Texture _txt;

        unsigned _currentSprite = 0;

        Item _inventory;
        sf::Vector2f _inventorypos;


};

#endif /* PLAYER_H */
