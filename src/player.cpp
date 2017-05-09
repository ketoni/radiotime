#include "player.hpp"

Player::Player(){
	texture.loadFromFile("./sprites/player.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
}

void Player::move(int x, int y){
	this->x += x;
	this->y += y;
	sprite.setPosition(x*texture.getSize().x,y*texture.getSize().y);
}

sf::Sprite& Player::getSprite() {
  return this->sprite;
}