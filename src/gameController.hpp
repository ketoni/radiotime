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
  sf::Clock clock;
  sf::RectangleShape shape;
  sf::RectangleShape shape1;



};
#endif
