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
  bool canMove;
  bool musicOn = false;
  bool startScreen = true;
  // The window to draw on
  sf::RenderWindow window;

  // Standart View
  sf::View view;
  Grid grid;
  Player player;
  //float beatTime = 1.025641025641f;
  float beatTime = 60.0f/117.2f;
  float hitWindow = 0.1f;
  sf::Texture gridTexture;
  sf::Sprite gridSprite;
  sf::Clock clock;
  sf::RectangleShape shape;
  sf::RectangleShape shape1;
  sf::Vector2u textPos = sf::Vector2u(240,950);
  TextBox textBox = TextBox(textPos, "Everyone knows that the best music comes from the 80's. Why not turn on the radio?", 26, sf::Color(255,0,0));
  std::vector<sf::Text> passwordLetters = std::vector<sf::Text>(5);
  std::string password = "STING";
  sf::Font font;



};
#endif
