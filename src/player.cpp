#include "player.hpp"

Player::Player(){
	texture.loadFromFile("../sprites/player.png");
	sprite.setTexture(texture);
	//sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
}

void Player::move(int x, int y){

	this->x += x;
	this->y += y;
	sprite.setPosition(this->x*texture.getSize().x,this->y*texture.getSize().y);
	std::cout << "penis" << sprite.getPosition().x << std::endl;
}

sf::Sprite& Player::getSprite() {
  return this->sprite;
}
