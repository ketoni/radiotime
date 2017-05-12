#include "player.hpp"


Player::Player() : _pos(2,2), _age(20), _inventory(), _inventorypos(1700.f, 540.f)
{

	setSprites();
	//sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
}

void Player::move(int x, int y)
{
	_originalPos.x = _pos.x*_textures[_currentSprite].getSize().x;
	_originalPos.y = _pos.y*_textures[_currentSprite].getSize().y;
	_pos.x += x;
    _pos.y += y;
    _moveAnimation = true;
    //right
    if(x == 1){
    	_faceDirection = 1;
    }
    //left
    else if(x == -1){;
		_faceDirection = 3;
	}
    //down
    else if(y == 1){2;
		_faceDirection = 2;
	}
    //up
    else if(y == -1){
		_faceDirection = 0;
	}
    if(_currentSprite != 16){
    	_currentSprite = _ageStep + _faceDirection;
    }

}

Item Player::swapInventory(Item item)
{
    Item ret = _inventory;
    _inventory = item;
    //if new item is not empty, start animation for it
    if(_inventory.texname != ""){
    	auto size = _inventory.sprite.getTexture()->getSize();
    	_inventory.sprite.setOrigin(size.x/2, size.y/2);
    	_inventory.sprite.setPosition(_inventorypos.x+size.x/2.0f,_inventorypos.y+ size.y/2.0f);
    	_inventory.sprite.setScale(5.0f,5.0f);
    	_inventoryAnimation = true;
    }
    //returned item has to be reseted
    ret.sprite.setOrigin(0, 0);
    ret.sprite.setScale(1.0f,1.0f);
    ret.sprite.setPosition(_inventorypos.x,_inventorypos.y);
    return ret;
} 

sf::Sprite& Player::getSprite()
{

    return _sprites[_currentSprite];
}

sf::Vector2i const& Player::getPosition()
{
    return _pos;
}

Item const& Player::getInventory()
{
    return _inventory;
}

void Player::setSprites() {

	_textures.reserve(17);
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			_textures.emplace_back();
			_textures.back().loadFromFile("../sprites/player/" + std::to_string(i) +"_" +std::to_string(j) + ".png");

			sf::Sprite sprite;
			_sprites.push_back(sprite);
			_sprites.back().setTexture(_textures.back());
		}
	}
	sf::Texture txt;
	txt.loadFromFile("../sprites/player/5.png");
	_textures.push_back(txt);

	sf::Sprite sprite;
	_sprites.push_back(sprite);
	_sprites[16].setTexture(_textures[16]);
	_sprites[_currentSprite].setPosition(220,185);

}

void Player::animate(){
	//item was taken recently into inventory -> animate it
	if(_inventoryAnimation){
		auto scale = _inventory.sprite.getScale();
		if(scale.x -0.1f <= 1.0f){
			_inventory.sprite.setScale(1.0f,1.0f);
			_inventoryAnimation = false;
		}
		else{
			_inventory.sprite.setScale(scale.x-0.1f,scale.y-0.1f);
		}
	}
	if(_moveAnimation){
		float x = 0.0f;
		float y = 0.0f;
		//up
		if(_faceDirection == 0){
			x = 0;
			//fast movement at the beginning
			if(_frame > 0){
				float factor = (float)-_frame/13;
				y = 20.0f*factor-90.0f;
			}
			else{
				y = -(13.0f+_frame)/13.0f*90.0f;
			}

		}
		//right
		else if(_faceDirection == 1){
			x = sqrt((-std::abs(_frame)/13.0f*30.0f+30.0f)/(1.0f/110.0f));
			y = -(30.0f-(1.0f/110.0f)*pow(_frame/13.0f*55,2.0));
			if(_frame > 0){
				x = 55+(55-x);
			}

		}
		//down
		else if(_faceDirection == 2){
			x = 0;
			//slow movement at the beginning
			if(_frame < 0){
				float factor = (float)-1.0f/_frame;
				y = 20.0f*factor;
			}
			else{
				y = _frame/13.0f*90.0f+20.0f;
			}


		}
		//left
		else if(_faceDirection == 3){
			x = -(sqrt((-std::abs(_frame)/13.0f*30.0f+30.0f)/(1.0f/110.0f)));
			y = -(30.0f-(1.0f/110.0f)*pow(_frame/13.0f*55,2.0));
			if(_frame > 0){
				x = -55+(-55-x);
			}

		}
		_sprites[_currentSprite].setPosition(_originalPos.x+x, _originalPos.y+y-35);
		_frame++;

	}
	if (_frame == 14){
		_frame = -13;
		_moveAnimation = false;
	}
}

bool Player::isMoving(){
	return _moveAnimation;
}

bool Player::age(){
	_ageCounter++;
	//player ages after certain amount of beats
	if(_ageCounter%_agingCooldown == 0){
		_age++;
		//player looks change after certain amount of years
		if(_currentSprite != 16 && _age % _ageStepCooldown == 0){
			_ageStep+=4;
			_currentSprite = _ageStep + _faceDirection;
			//player reaches "death"
			if(_ageStep == 16){
				_currentSprite = 16;
				_sprites[_currentSprite].setPosition(_pos.x*110,_pos.y*110-35);
				return false;
			}
			_sprites[_currentSprite].setPosition(_pos.x*110,_pos.y*110-35);

		}
	}
	return true;

}
unsigned Player::getAge(){
	return _age;


}
