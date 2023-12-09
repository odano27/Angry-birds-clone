#include "Game.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>

#include "CompletedMenu.h"
#include "DebugDraw.h"
#include "Entities.h"
#include "HUD.h"

Game::Game(sf::RenderWindow& window) : _window(window) {
  _level = nullptr;
  _input = new Input(window);
  _renderer = new Renderer(window);
  _eventBus = new GameEventBus();
  _physics = new Physics(*_renderer);

  _assets = new AssetLoader();
  _assets->LoadLevels();

  _uiManager = new UIManager(*_eventBus, *_assets, _renderer->GetWindowSize());
  _input->AddEventHandler(sf::Event::MouseButtonPressed, _uiManager);

  _eventBus->AddEventHandler(GameEvent::StartLevel, this);
  _eventBus->AddEventHandler(GameEvent::RestartLevel, this);
  _eventBus->AddEventHandler(GameEvent::LevelCompleted, this);
  _eventBus->AddEventHandler(GameEvent::NextLevel, this);
  _eventBus->AddEventHandler(GameEvent::BackToMenu, this);

  _uiManager->Show(UIScreenType::MainMenu);
}

Game::~Game() {
  delete _level;
  delete _input;
  delete _renderer;
  delete _physics;
  delete _uiManager;
  delete _assets;
  delete _eventBus;
}

void Game::RunLoop() {
  double fixedDeltaTime = 1.0 / 50;
  double maxDeltaTime = 1.0 / 3.0;

  sf::Clock clock;
  double accumulated = 0.0;
  while (_window.isOpen()) {
    double elapsed = clock.restart().asSeconds();

    if (elapsed > maxDeltaTime) elapsed = maxDeltaTime;
    accumulated += elapsed;

    // Process Input
    _input->ProcessEvents();

    // Process Game Events
    _eventBus->ProcessEvents();

    while (accumulated >= fixedDeltaTime) {
      // Update Physics
      _physics->FixedUpdate(fixedDeltaTime);

      accumulated -= fixedDeltaTime;
    }

    // Rendering
    {
      double t = accumulated / fixedDeltaTime;
      RenderScope scope(*_renderer);

      // Draw Level
      if (_level != nullptr) _level->Draw(*_renderer, t);

      // Draw physics debug overlay
      if (_input->IsKeyPressed(sf::Keyboard::Scan::D)) _physics->DrawDebug();

      // Draw UI
      _uiManager->Draw(*_renderer);
    }
  }
}

void Game::HandleGameEvent(const GameEvent& event) {
  if (event.type == GameEvent::StartLevel) {
    int levelIndex = event.startLevel.index;
    _level = new Level(*_renderer, *_physics, *_eventBus, *_assets);
    _level->CreateLevel(levelIndex);

    HUD::Data data{levelIndex, _level->GetEnemiesTotal(),
                   _level->GetAmountByBird()};
    _uiManager->Show(UIScreenType::HUD, &data);

    _input->AddEventHandler(sf::Event::MouseMoved, _level);
    _input->AddEventHandler(sf::Event::MouseButtonPressed, _level);
    _input->AddEventHandler(sf::Event::MouseButtonReleased, _level);
  } else if (event.type == GameEvent::RestartLevel) {
    _level->RestartLevel();
  } else if (event.type == GameEvent::LevelCompleted) {
    CompletedMenu::Data data{event.levelCompleted.lastLevel,
                             event.levelCompleted.levelFailed};
    _uiManager->Show(UIScreenType::CompletedMenu, &data);
  } else if (event.type == GameEvent::NextLevel) {
    _level->NextLevel();
  } else if (event.type == GameEvent::BackToMenu) {
    _uiManager->HideAll();
    _uiManager->Show(UIScreenType::MainMenu);

    _input->RemoveEventHandler(sf::Event::MouseMoved, _level);
    _input->RemoveEventHandler(sf::Event::MouseButtonPressed, _level);
    _input->RemoveEventHandler(sf::Event::MouseButtonReleased, _level);

    delete _level;
    _level = nullptr;
  }
}