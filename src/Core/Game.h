#pragma once

#include "AssetLoader.h"
#include "GameEvent.h"
#include "Input.h"
#include "Physics.h"
#include "Renderer.h"
#include "UIManager.h"
#include "level.hpp"

class Game : public IGameEventHandler {
 public:
  Game(sf::RenderWindow& window);
  ~Game();

  void RunLoop();

  void HandleGameEvent(const GameEvent& event) override;

 private:
  sf::RenderWindow& _window;

  Input* _input;
  Physics* _physics;
  Renderer* _renderer;
  Level* _level;
  UIManager* _uiManager;
  AssetLoader* _assets;
  GameEventBus* _eventBus;
};