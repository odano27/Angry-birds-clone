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

  void RunLoop();

  void HandleGameEvent(const GameEvent& event) override;

 private:
  sf::RenderWindow& _window;

  AssetLoader _assets;
  Renderer _renderer;
  Physics _physics;
  GameEventBus _eventBus;
  UIManager _uiManager;
  Input _input;
  sf::SoundBuffer _soundBuffer[3];
	sf::Sound _Sounds[3];

  std::unique_ptr<Level> _level;
}

;