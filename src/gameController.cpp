#include "gameController.hpp"

#include <cmath>

GameController::GameController() : exitRequested(false), window(sf::VideoMode(1920,1080), "RadioTime", sf::Style::Fullscreen), view(sf::FloatRect(0,0,1920,1080))
{
	window.setFramerateLimit(60);
	
    shape.setFillColor(sf::Color(0,200,0));
	shape.setPosition(446,454);
	
    shape1.setFillColor(sf::Color(200,200,200));
    shape1.setPosition(446,454);
	shape1.setSize(sf::Vector2f(200,40));
	
    inventorybox.setFillColor(sf::Color(49, 254, 222));
    inventorybox.setPosition(1700.f, 440.f);
    inventorybox.setSize({110, 110});
    
    window.setView(view);
	clock.restart();
	gridTexture.loadFromFile("../sprites/grid.png");
	gridSprite.setTexture(gridTexture);
	gridSprite.setPosition(-10,0);

	startTexture.loadFromFile("../sprites/start.png");
	startSprite.setTexture(startTexture);

	arrowTexture.loadFromFile("../sprites/arrow.png");
	arrowSprite.setTexture(arrowTexture);
	arrowSprite.setPosition(220,0);

	//gridSprite.setScale((float)(1200.0f/1920.0f),(float)(675.0f/1080.0f));
	//gridSprite.setScale(0.1f,0.1f);
	font.loadFromFile("../fonts/PressStart2P.ttf");
	int i = 0;
	int x = 36;
	for(int i = 0; i < password.length(); i++){
		passwordLetters[i].setString("?");
		passwordLetters[i].setCharacterSize(30);
		passwordLetters[i].setFont(font);
		passwordLetters[i].setPosition(417+x*i,34);
	}
	ageText.setFont(font);
	ageText.setPosition(1670,300);
	ageText.setString("AGE:"+std::to_string(player.getAge()));

}

void GameController::run()
{

	music.openFromFile("../music/music.ogg");
	float factor = 0.0f;
	float time = 0.0f;
	// start screen, wait for player to press something
	while(window.isOpen() && !exitRequested && startScreen) {
		sf::Event event1;
		while(window.pollEvent(event1)) {
			if (event1.type == sf::Event::Closed || (event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Escape))
			{
				exitRequested = true;
			}
			if(event1.type == sf::Event::KeyPressed) {
				startScreen = false;
			}
		}
		time = clock.getElapsedTime().asSeconds();
		factor = std::fmod(time, beatTime);
		if(factor > beatTime/2.0f){
			startBox.getText().setColor(sf::Color((beatTime-factor)*130+120,(beatTime-factor)*40+200,(beatTime-factor)*27+27));
		}
		else{
			startBox.getText().setColor(sf::Color(factor*130+120,factor*40+200,factor*27+27));
		}
		window.clear(sf::Color(0,0,0));
		window.draw(startSprite);
		window.draw(startBox.getBox());
		window.draw(startBox.getText());
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
			if(!aged && factor <beatTime/10){
				if(!player.age()){
					end(false);
				}
				aged = true;
			}
			if(aged && factor >beatTime/2){
				aged = false;
			}
			if (!canMove && factor > hitWindow && factor < beatTime-hitWindow){
				canMove = true;
			}
		}
		//player can move off beat before the music is turned on
		else{
			if(!player.isMoving()){
				canMove = true;
			}
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
			if(keyReleased && canMove && event.type == sf::Event::KeyPressed && (!musicOn ||(std::abs(factor-beatTime)<hitWindow || factor<hitWindow))){
				keyReleased = false;
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
				if(event.key.code == sf::Keyboard::N){
					letterFound('N');
				}
				//std::cout << "time " << std::fmod(time, beatTime) << std::endl;
			}
			if(event.type == sf::Event::KeyReleased){
				keyReleased = true;
			}

		}


    // a block shows when to beat
	if(musicOn){
		shape.setSize(sf::Vector2f((beatTime*2-(beatTime-factor))*200,40));
	}
	//arrow over radio
	else{
		time = clock.getElapsedTime().asSeconds();
		float factor2 = std::fmod(time, beatTime);
		arrowSprite.setPosition(226,factor2*-50);
	}
	// clear window with color according to the beat (the color pulses)
	window.clear(sf::Color((beatTime-factor)*50,(beatTime-factor)*50,(beatTime-factor)*50));

	player.animate();
	ageText.setString("AGE: "+std::to_string(player.getAge()));
    // Draw everything to screen
    draw();

    // Update frame
    window.display();
  }
}
// logic for player movement
void GameController::playerMove(int x, int y){
    static sf::Vector2i newpos;
    newpos = player.getPosition() + sf::Vector2i(x,y);

    if (grid.canMoveTo(newpos.x, newpos.y)) {
        // Tile can be moved on
        player.move(x,y);
    }
    else if (grid.canInteractWith(newpos.x, newpos.y)) {
        // Tile can't be moved on, but could hold items
        Tile& tile = grid.getTile(newpos.x, newpos.y);
      
        // storage object
        if (tile.puzzlekey == -1) {
            textBox.setInfoText(TextBox::SwapItems, tile, player.getInventory());
            tile.storage = player.swapInventory(tile.storage);
            tile.storage.sprite.setPosition(newpos.x * grid.getTileSize(), newpos.y * grid.getTileSize());
        }
        // puzzle object
        else if (tile.puzzlekey == player.getInventory().id) {
            tile.storage = player.swapInventory(tile.puzzlepiece);
            std::cout << player.getInventory().texname << std::endl;
            if (player.getInventory().texname.length() == 1) {
                // found a password letter
                letterFound(player.getInventory().texname[0]);
                textBox.setInfoText(TextBox::UnlockLetter, tile);
            }
            else {
                // puzzle progress
                textBox.setInfoText(TextBox::PuzzleProgress, tile, tile.storage);
            }
            tile.storage = {0};
            tile.storeable = false;
        }
        // nothing interesting happens
        else if (player.getInventory().id == 0){
            // examine
            textBox.setInfoText(TextBox::ObjectExamine, tile);
        }
        else {
            // wrong object
            textBox.setInfoText(TextBox::NothingHappens, tile, player.getInventory());
        }
    }
    //radio interact
    else if (!musicOn && newpos.x == 2 && newpos.y == 0){
    	musicOn = true;
    	music.play();
    	textBox.setText("Uh oh! The time machine has tuned to the beat! Shut it off before you DIE.");
        // Tile just blocks movement 
    }
	canMove = false;
}

//draw everything
void GameController::draw() {

		window.draw(gridSprite);
		if(!musicOn){
			window.draw(arrowSprite);
		}
		window.draw(player.getSprite());
		window.draw(shape1);
		window.draw(shape);
		window.draw(inventorybox);
		window.draw(ageText);
		//window.draw(textBox.getBox());
		window.draw(textBox.getText());
		for(auto text : passwordLetters) {
			window.draw(text);
		}

        for (auto& tile : grid.getTiles()) {
            window.draw(tile.sprite);
            if (tile.storage.id && !tile.hidden) {
                window.draw(tile.storage.sprite);
            }
        }
        window.draw(player.getInventory().sprite);
        window.draw(endBox.getText());

}

void GameController::letterFound(char letter){
	for(int i = 0; i < password.length(); i++){
		if (password[i] == letter){
			passwordLetters[i].setString(letter);
		}
	}
}

void GameController::end(bool win){
	if(!win){
		endBox.setText("Poor you.. You had all the time in the world to figure out the puzzle.. but then you turned into stone.. poor you..");
	}
	else{
		endBox.setText("WIN");
	}

}
