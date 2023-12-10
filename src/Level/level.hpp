#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>

#include "Birds.h"
#include "GameEvent.h"
#include "Input.h"
#include "leveldata.hpp"

class Level : public IInputEventHandler, public IGameEventHandler {
 public:
  static constexpr float SPEED_MULT = 5.0f;

  Level(Renderer& renderer, Physics& physics, GameEventBus& eventBus,
        AssetLoader& assets);
  ~Level();

  void Draw(Renderer& renderer, double t);
  void HandleInputEvent(const sf::Event& event) override;
  void HandleGameEvent(const GameEvent& event) override;

  void CreateLevel(int levelIndex);
  void RestartLevel();
  void NextLevel();

  int GetEnemiesTotal() const;
  const std::map<BirdType, int>& GetAmountByBird() const;

  void Update(double deltaTime);

 private:
  Renderer& _renderer;
  Physics& _physics;
  GameEventBus& _eventBus;
  AssetLoader& _assets;

  std::vector<std::unique_ptr<Entities>> _entities;
  int _slingshotIndex;
  int _previewIndex;
  int _lastBirdIndex;

  bool _levelCompleted;
  int _levelIndex;
  int _enemiesTotal;
  int _enemiesDestroyed;
  std::map<BirdType, int> _amountByBird;
  BirdType _selected;

  void ClearLevel();

  void UpdateHUD() const;
  int GetAngle(int mouseX, int mouseY, sf::Vector2f origin) const;

  int AddEntity(Entities*&& entity);
  void RemoveEntity(int index);
  Entities& GetEntity(int index) const;
};

#endif  // _LEVEL_HPP_
