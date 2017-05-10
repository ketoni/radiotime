#include "player.hpp"

Player::Player() : _pos(0,0), _age(0), _sprite(), _texture(), _inventory(), _inventorypos(100.f, 100.f)
{
	_texture.loadFromFile("../sprites/player.png");
	_sprite.setTexture(_texture);
	//sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
}

void Player::move(int x, int y)
{
	_pos.x += x;
    _pos.y += y;
	_sprite.setPosition(_pos.x * _texture.getSize().x, _pos.y * _texture.getSize().y);
}

Item Player::swapInventory(Item item)
{
    Item ret = _inventory;
    _inventory = item;
    _inventory.sprite.setPosition(_inventorypos);
    return ret;
} 

sf::Sprite& Player::getSprite()
{
    return _sprite;
}

sf::Vector2i const& Player::getPosition()
{
    return _pos;
}

Item const& Player::getInventory()
{
    return _inventory;
}
