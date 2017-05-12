#include "gameController.hpp"

#include <cmath>

GameController::GameController() : exitRequested(false), window(sf::VideoMode(1920,1080), "RadioTime", sf::Style::Fullscreen), view(sf::FloatRect(0,0,1920,1080))
{
	window.setFramerateLimit(60);
	
    shape.setFillColor(sf::Color(0,200,0));
	shape.setPosition(446,455);

    shape1.setFillColor(sf::Color(200,200,200));
    shape1.setPosition(446,455);
	shape1.setSize(sf::Vector2f(100,40));

    inventorybox.setFillColor(sf::Color(49, 254, 222));
    inventorybox.setPosition(1700.f, 540.f);
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

	inventoryText.setFont(font);
	inventoryText.setPosition(1670,480);
	inventoryText.setString("PICK UP");
	setSprites();

	soundBuffers["DEATH"].loadFromFile("../sounds/DEATH.wav");
	soundBuffers["FAILED_INTERACTION"].loadFromFile("../sounds/FAILED_INTERACTION.wav");
	soundBuffers["LETTER_REVEAL"].loadFromFile("../sounds/LETTER_REVEAL.wav");
	soundBuffers["PICKUP"].loadFromFile("../sounds/PICKUP.wav");
	soundBuffers["SWITCH"].loadFromFile("../sounds/SWITCH.wav");
	soundBuffers["WIN"].loadFromFile("../sounds/WIN.wav");

	sounds["DEATH"].setBuffer(soundBuffers["DEATH"]);
	sounds["FAILED_INTERACTION"].setBuffer(soundBuffers["FAILED_INTERACTION"]);
	sounds["LETTER_REVEAL"].setBuffer(soundBuffers["LETTER_REVEAL"]);
	sounds["PICKUP"].setBuffer(soundBuffers["PICKUP"]);
	sounds["SWITCH"].setBuffer(soundBuffers["SWITCH"]);
	sounds["WIN"].setBuffer(soundBuffers["WIN"]);

}
void GameController::setSprites() {

	animationTextures.reserve(73);
	for (int i = 1; i < 74; i++) {
		animationTextures.emplace_back();
		std::string thing = "../sprites/ANIMATION/BOUNCE/animation0";
		if(i < 100){
			thing += "0";
		}
		if(i < 10){
			thing += "0";
		}
		animationTextures.back().loadFromFile(thing + std::to_string(i) + ".png");

		sf::Sprite sprite;
		animationSprites.push_back(sprite);
		animationSprites.back().setTexture(animationTextures.back());
		animationSprites.back().setPosition(-10,0);
	}
	starTextures.reserve(65);
	for (int i = 2; i < 130; i+=2) {
		starTextures.emplace_back();
		std::string thing = "../sprites/ANIMATION/STARS/STARS0";
		if(i < 100){
			thing += "0";
		}
		if(i < 10){
			thing += "0";
		}
		starTextures.back().loadFromFile(thing + std::to_string(i) + ".png");

		sf::Sprite sprite;
		starSprites.push_back(sprite);
		starSprites.back().setTexture(starTextures.back());
		starSprites.back().setPosition(-10,0);
	}

}
void GameController::run()
{

	music.openFromFile("../music/music.ogg");
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
				if(event.key.code == sf::Keyboard::W){
					end(true);
				}
				//std::cout << "time " << std::fmod(time, beatTime) << std::endl;
			}
			if(event.type == sf::Event::KeyReleased){
				keyReleased = true;
			}

		}


    // a block shows when to beat
	if(musicOn){
		shape.setSize(sf::Vector2f((beatTime*2-(beatTime-factor))*100,40));
		animate();
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

    if(canInteract){
    	if(factor > beatTime/2.0f){
			endBox.getText().setColor(sf::Color((beatTime-factor)*50+50,(beatTime-factor)*100+150,(beatTime-factor)*100+150));
		}
		else{
			endBox.getText().setColor(sf::Color(factor*50+50,factor*100+150,factor*100+150));
		}
    }
    else{
    	if(factor > beatTime/2.0f){
			endBox.getText().setColor(sf::Color((beatTime-factor)*75+130,(beatTime-factor)*40+40,(beatTime-factor)*40+40));
		}
		else{
			endBox.getText().setColor(sf::Color(factor*75+130,factor*40+40,factor*40+40));
		}
    }
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
    else if (canInteract && grid.canInteractWith(newpos.x, newpos.y)) {
        // Tile can't be moved on, but could hold items
        Tile& tile = grid.getTile(newpos.x, newpos.y);
      
        // storage object
        if (tile.puzzlekey == -1) {
        	sounds["PICKUP"].play();
            textBox.setInfoText(TextBox::SwapItems, tile, player.getInventory());
            tile.storage = player.swapInventory(tile.storage);
            tile.storage.sprite.setPosition(newpos.x * grid.getTileSize(), newpos.y * grid.getTileSize());
        }
        // puzzle object
        else if (tile.puzzlekey == player.getInventory().id) {
        	sounds["SWITCH"].play();
            tile.storage = player.swapInventory(tile.puzzlepiece);
            std::cout << player.getInventory().texname << std::endl;
            if (player.getInventory().texname.length() == 1) {
                // found a password letter
                letterFound(player.getInventory().texname[0]);
                sounds["LETTER_REVEAL"].play();
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
        	sounds["FAILED_INTERACTION"].play();
            textBox.setInfoText(TextBox::NothingHappens, tile, player.getInventory());
        }
    }
    //radio interact
    else if (!musicOn && newpos.x == 2 && newpos.y == 0){
    	musicOn = true;
    	canInteract = true;
    	music.play();
    	textBox.setText("Uh oh! My time machine is tuned to the music, and I'm aging fast! Go to the console.");
    	music.setLoop(true);
        // Tile just blocks movement 
    }
    else if (grid.getTile(newpos.x, newpos.y).puzzlehint.length()) {
        textBox.setText(grid.getTile(newpos.x, newpos.y).puzzlehint);
    }
	canMove = false;
}

//draw everything
void GameController::draw() {

	if(musicOn){
		window.draw(starSprites[currentAnimSprite]);
	}
	else{
		window.draw(starSprites[0]);
	}
	window.draw(gridSprite);
	if(!musicOn){
		window.draw(animationSprites[0]);
		window.draw(arrowSprite);
	}
	else{
		//std::cout << "index " << currentAnimSprite << std::endl;
		window.draw(animationSprites[currentAnimSprite]);
	}
	window.draw(player.getSprite());
	window.draw(shape1);
	window.draw(shape);
	window.draw(inventorybox);
	window.draw(ageText);
	window.draw(inventoryText);
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
void GameController::animate() {
	currentAnimSprite += 1;
	if(!aged && factor <beatTime/10){
		aged = true;
		currentAnimSprite = 0;
	}

}

void GameController::letterFound(char letter){
	for(int i = 0; i < password.length(); i++){
		if (password[i] == letter){
			passwordLetters[i].setString(letter);
		}
	}
    for (auto letter : passwordLetters) {
        if (letter.getString() == "?") {
            return;
        }
    }
    end(true);
}

void GameController::end(bool win){

	if(!hasEnded){
		if(!win){
			sounds["DEATH"].play();
			endBox.setText("YOU LOSE");
			textBox.setText("Poor you.. You had all the time in the world to figure out the puzzle.. but then you turned into stone.. poor you..");
			endBox.getText().setColor(sf::Color(150,80,80));
			canInteract = false;

		}
		else{
			sounds["WIN"].play();
			endBox.setText("YOU WIN");
			textBox.setText("You managed to shut down the time machine! Don't worry, you still have some good years left!");
			endBox.getText().setColor(sf::Color(100,255,255));
		}
		hasEnded = true;
	}


}
