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
  ~Player();
  int x = 0;
  int y = 0;
  sf::Sprite& getSprite();
  void move(int,int);

private:
  int age = 0;
  sf::Sprite sprite;
  sf::Texture texture;
  Item *item;

};

#endif /* PLAYER_H */
