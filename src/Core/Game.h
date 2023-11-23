#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AssetLoader.h"
#include "Input.h"
#include "Physics.h"
#include "Renderer.h"
#include "UIManager.h"
#include "level.hpp"

class Game {
 public:
  Game(sf::RenderWindow& window);
  ~Game();

  const sf::Texture& shapeToTexture(
      const sf::Shape& shape, float sizex,
      float sizey);  // for testing, actual implementation could be in a
                     // different class
  void RunLoop();

 private:
  void CreateTestLevel();
  void DeleteLevel();

  sf::RenderWindow& _window;
  std::vector<std::unique_ptr<sf::Texture>>
      textures;  // a vector that holds all the textures for the game
  std::vector<std::unique_ptr<sf::RenderTexture>>
      renderTextures;  // a vector that holds all the render textures (from
                       // shapes) for the game

  Input* _input;
  Physics* _physics;
  Renderer* _renderer;
  Level* _level;
  UIManager* _uiManager;
  AssetLoader* _assets;
};