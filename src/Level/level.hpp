#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>

#include "Birds.h"
#include "GameEvent.h"
#include "leveldata.hpp"

class Level {
 public:
  Level(Physics& physics, GameEventBus& eventBus, AssetLoader& assets);
  ~Level();

  void loadLevel(LevelData& data);
  bool isCompleted() const;
  int calculateScore();

  void Draw(Renderer& renderer, double t);

  void CerateLevel(int levelIndex, Renderer& renderer);
  void RestartLevel(Renderer& renderer);

 private:
  Physics& _physics;
  GameEventBus& _eventBus;
  AssetLoader& _assets;

  std::vector<std::unique_ptr<Entities>> _entities;
  std::unique_ptr<Birds> _activeBird;

  int score;
  bool levelComplete;
  int _levelIndex;

  void CreateLevel1(Renderer& renderer);
  void CreateLevel2(Renderer& renderer);
  void CreateLevel3(Renderer& renderer);

  void AddEntity(Entities*&& entity);
};

#endif  // _LEVEL_HPP_
