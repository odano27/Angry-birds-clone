#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>

#include "Birds.h"
#include "GameEvent.h"
#include "Input.h"
#include "leveldata.hpp"

class Level : public IInputEventHandler {
 public:
  Level(Renderer& renderer, Physics& physics, GameEventBus& eventBus,
        AssetLoader& assets);
  ~Level();

  void loadLevel(LevelData& data);
  bool isCompleted() const;
  int calculateScore();

  void Draw(Renderer& renderer, double t);
  void HandleInputEvent(const sf::Event& event) override;

  void CerateLevel(int levelIndex);
  void RestartLevel();

 private:
  Renderer& _renderer;
  Physics& _physics;
  GameEventBus& _eventBus;
  AssetLoader& _assets;

  std::vector<std::unique_ptr<Entities>> _entities;
  int _slingshotIndex;
  int _previewIndex;

  int score;
  bool levelComplete;
  int _levelIndex;

  void CreateCommon();
  void CreateLevel1();
  void CreateLevel2();
  void CreateLevel3();

  int AddEntity(Entities*&& entity);
  void RemoveEntity(int index);
  Entities& GetEntity(int index);
};

#endif  // _LEVEL_HPP_
