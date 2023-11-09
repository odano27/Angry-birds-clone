#pragma once

#include <SFML/Graphics.hpp>

#include "Input.h"
#include "Physics.h"
#include "Renderer.h"
#include "level.hpp"

class Game {
 public:
  Game(sf::RenderWindow& window);
  ~Game();

  void RunLoop();

 private:
  void CreateTestLevel();
  void DeleteLevel();

  sf::RenderWindow& _window;

  Input* _input;
  Physics* _physics;
  Renderer* _renderer;
  Level* _level;
};