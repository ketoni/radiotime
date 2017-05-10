#include "gameController.hpp"

#include <cmath>

GameController::GameController() : exitRequested(false), window(sf::VideoMode(1080,720), "RadioTime", sf::Style::Close), view(sf::FloatRect(0,0,800,600))
{
  window.setFramerateLimit(60);
  shape.setFillColor(sf::Color(0,200,0));
  shape.setPosition(500,500);
  shape1.setFillColor(sf::Color(200,200,200));
  shape1.setPosition(500,500);
  shape1.setSize(sf::Vector2f(200,40));
  window.setView(view);
  clock.restart();

}

void GameController::run()
{
	sf::Music music;
	music.openFromFile("../music/music.ogg");
	float factor = 0.0f;
	float time = 0.0f;

	// start screen, wait for player to press something
	while(window.isOpen() && !exitRequested && startScreen){
		sf::Event event1;
		while(window.pollEvent(event1)){
			if (event1.type == sf::Event::Closed || (event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Escape))
			{
				exitRequested = true;
			}
			if(event1.type == sf::Event::KeyPressed){
				startScreen = false;
			}
		}
		window.clear(sf::Color(0,0,0));
		window.display();
	}

	// Game begins
	while(window.isOpen() && !exitRequested)
	{
		sf::Event event;
		//if music is on, change the factors which determine whether the player can move yet or not
		if(musicOn){
			time = music.getPlayingOffset().asSeconds();
			factor = std::fmod(time, beatTime);
			if (factor > hitWindow && factor < beatTime-hitWindow){
				canMove = true;
			}
		}
		//player can move arbitraly before the music is turned on
		else{
			canMove = true;
		}

		while(window.pollEvent(event))
		{
			//exit
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				exitRequested = true;
			}
			//player movement, can move always if music is off
			// if music is on, only one movement per beat
			if(canMove && event.type == sf::Event::KeyPressed && (!musicOn ||(std::abs(factor-beatTime)<hitWindow || factor<hitWindow))){
				if(event.key.code == sf::Keyboard::Left){
					playerMove(-1,0);
				}
				else if(event.key.code == sf::Keyboard::Right){
					playerMove(1,0);
				}
				else if(event.key.code == sf::Keyboard::Down){
					playerMove(0,1);
				}
				else if(event.key.code == sf::Keyboard::Up){
					playerMove(0,-1);
				}
				if(!musicOn && event.key.code == sf::Keyboard::P){
					musicOn = true;
					music.play();
				}
				std::cout << "time " << std::fmod(time, beatTime) << std::endl;
			}

		}

    // a block shows when to beat
	if(musicOn){
		shape.setSize(sf::Vector2f((beatTime*2-(beatTime-factor))*200,40));
	}
	// clear window with color according to the beat (the color pulses)
	window.clear(sf::Color((beatTime-factor)*50,(beatTime-factor)*50,(beatTime-factor)*50));

    // Draw everything to screen
    draw();

    // Update frame
    window.display();
  }
}
// logic for player movement
void GameController::playerMove(int x, int y){

	if(grid.getHeight() > player.y + y && player.y >= 0){
		if(grid.getWidth() > player.x + x && player.x >= 0){
			std::cout << grid.getTiles()[player.x+x+(player.y+y)*grid.getWidth()].texname.length() << std::endl;
			//check if tile is empty
			if(!(grid.getTiles()[player.x+x+(player.y+y)*grid.getWidth()].texname.length())){
				player.move(x,y);
			}

		}
	}
	canMove = false;
}

//draw everything
void GameController::draw() {

        for (auto& tile : grid.getTiles()) {
            window.draw(tile.sprite);
            if (tile.storage.id) {
                window.draw(tile.storage.sprite);
            }
        }

		auto playerSprite = player.getSprite();
		window.draw(playerSprite);
		window.draw(shape1);
		window.draw(shape);

}
