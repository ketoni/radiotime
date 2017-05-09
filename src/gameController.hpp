#ifndef Game_h__
#define Game_h__


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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
  // The window to draw on
  sf::RenderWindow window;

  // Standart View
  sf::View view;
  Grid grid = Grid(10,10);
  Player player;
  float beatTime = 1.0f;
  float hitWindow = 0.1f;
  sf::Clock clock;
  sf::RectangleShape shape;


};
#endif
