#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "item.hpp"

class Player
{
    public:
        Player();
        
        sf::Vector2i const& getPosition();
        sf::Sprite& getSprite();
        Item const& getInventory();

        void move(int, int);
        Item swapInventory(Item);

    private:

        sf::Vector2i _pos;
        unsigned _age;
        
        sf::Sprite _sprite;
        sf::Texture _texture;

        Item _inventory;
        sf::Vector2f _inventorypos;
};

#endif /* PLAYER_H */
