#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>

#include "Birds.h"
#include "Entities.h"
#include "Renderer.h"
#include "leveldata.hpp"
#include "Physics.h"

class Level {
 public:
  Level();
  ~Level();

  void loadLevel(LevelData& data);
  bool isCompleted() const;
  int calculateScore();

  void Draw(Renderer& renderer, double t);

  void AddEntity(Entities* entity);

  const std::vector<Entities*>& GetEntities() const;

  void SwitchToLevel(int levelNumber);

 private:
  std::vector<Entities*> entities;
  Birds* activeBird;
  int score;
  bool levelComplete;
  int currentLevel;

  void CreateLevel1();

  void CreateLevel2();

  void CreateLevel3();
};

#endif  // _LEVEL_HPP_
