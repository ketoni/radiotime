#include "gameController.hpp"


GameController::GameController() : exitRequested(false), window(sf::VideoMode(1080,720), "RadioTime", sf::Style::Close), view(sf::FloatRect(0,0,800,600))
{
  window.setFramerateLimit(60);
  shape.setFillColor(sf::Color(0,200,0));
  shape.setPosition(500,500);
  window.setView(view);
  clock.restart();
}

void GameController::run()
{
  // Loop until the player exits the game
  while(window.isOpen() && !exitRequested)
  {
    // Check for events happening
    sf::Event event;
    float time = clock.getElapsedTime().asSeconds();
    float factor = std::fmod(time, beatTime);
    if (factor > hitWindow && factor < beatTime-hitWindow){
    	canMove = true;
    }
    while(window.pollEvent(event))
    {
      // Check if something needs to be done with given event


    	if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
    	{
    		exitRequested = true;
    	}
    	if(canMove && event.type == sf::Event::KeyPressed && (std::abs(factor-beatTime)<hitWindow || factor<hitWindow)){
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

    		std::cout << "time " << std::fmod(time, beatTime) << std::endl;
    	}

    }
    // Update everything that is needed
    // Enemy movement, tower shooting etc.

    // Clear window
    shape.setSize(sf::Vector2f(factor*200,40));
    window.clear(sf::Color((1-factor)*50,(1-factor)*50,(1-factor)*50));

    // Draw everything to screen
    draw();

    // Update frame
    window.display();
  }
}

void GameController::playerMove(int x, int y){

	//std::cout << "direction " << x << " " << y << std::endl;
	//std::cout << "player position " << player.x << " " << player.y << std::endl;
	//std::cout << "grid size " << grid.height << " " << grid.width << std::endl;
	if(grid.height > player.y + y && player.y >= 0){
		if(grid.width > player.x + x && player.x >= 0){
			//grid.tiles[player->x][player->y] = nullptr;
			//grid.tiles[player->x+x][player->y+y] = player;
			player.move(x,y);

		}
	}
	canMove = false;
}

void GameController::draw() {

		auto playerSprite = player.getSprite();
		window.draw(playerSprite);
		window.draw(shape);

}
