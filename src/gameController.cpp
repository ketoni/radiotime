#include "gameController.hpp"


GameController::GameController() : exitRequested(false), window(sf::VideoMode(800,600), "RadioTime", sf::Style::Close), view(sf::FloatRect(0,0,800,600))
{
  window.setFramerateLimit(60);

  window.setView(view);
}

void GameController::run()
{
  // Loop until the player exits the game
  while(window.isOpen() && !exitRequested)
  {
    // Check for events happening
    sf::Event event;

    while(window.pollEvent(event))
    {
      // Check if something needs to be done with given event

      if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
      {
        exitRequested = true;
      }
      else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left){
      	playerMove(-1,0);
      }
      else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
      	playerMove(1,0);
			}
      else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
      	playerMove(0,1);
			}
      else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
      	playerMove(0,-1);
			}
    }

    // Update everything that is needed
    // Enemy movement, tower shooting etc.

    // Clear window
    window.clear(sf::Color(0,0,0));

    // Draw everything to screen
    draw();

    // Update frame
    window.display();
  }
}

void GameController::playerMove(int x, int y){

	if(grid.height > player.y + y && player.y >= 0){
		if(grid.width > player.x + x && player.x >= 0){
			//grid.tiles[player->x][player->y] = nullptr;
			//grid.tiles[player->x+x][player->y+y] = player;
			player.move(x,y);

		}
	}
}

void GameController::draw() {

		auto playerSprite = player.getSprite();
		window.draw(playerSprite);

}
