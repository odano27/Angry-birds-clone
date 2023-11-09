#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>

#include "Birds.h"
#include "Entities.h"
#include "Renderer.h"
#include "leveldata.hpp"

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

 private:
  std::vector<Entities*> entities;
  Birds* activeBird;
  int enemyCount;
  int score;
  bool levelComplete;
};

#endif  // _LEVEL_HPP_
