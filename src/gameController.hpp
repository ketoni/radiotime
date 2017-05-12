#ifndef Game_h__
#define Game_h__


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <list>
#include <iostream>
#include "player.hpp"
#include "grid.hpp"
#include "textBox.hpp"

class GameController
{
public:
  GameController();
  ~GameController(){};

  void run();
  void playerMove(int,int);
  void draw();
  void end(bool);
  void exit()
  {
  exitRequested = true;
  }
  void letterFound(char);

  sf::RenderWindow& getWindow()
  {
  return window;
  }


private:

  // Exit the game
  bool exitRequested;
  bool keyReleased = true;
  bool canMove;
  bool aged;
  bool musicOn = false;
  bool startScreen = true;
  // The window to draw on
  sf::RenderWindow window;

  // Standart View
  sf::View view;
  Grid grid;
  Player player;
  float beatTime = 120.0f/117.2f;
  float hitWindow = 0.1f;
  sf::Texture startTexture;
  sf::Sprite startSprite;
  TextBox startBox = TextBox(sf::Vector2u(500,900),"Press any key to start", 40, sf::Color(255,240,57));
  sf::Texture gridTexture;
  sf::Sprite gridSprite;
  sf::Texture arrowTexture;
  sf::Sprite arrowSprite;
  sf::Clock clock;
  sf::RectangleShape shape;
  sf::RectangleShape shape1;
  sf::RectangleShape inventorybox;
  sf::Vector2u textPos = sf::Vector2u(240,950);
  TextBox textBox = TextBox(textPos, "Everyone knows that the best music comes from the 80's. Why not turn on the radio?", 30, sf::Color(67,221,192));
  TextBox endBox = TextBox(sf::Vector2u(240,500), "", 30, sf::Color(0,0,0));
  sf::Music music;
  sf::Text ageText;
  std::vector<sf::Text> passwordLetters = std::vector<sf::Text>(5);
  std::string password = "STING";
  sf::Font font;



};
#endif
