#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>
#include <iostream>
#include "Birds.h"
#include "Entities.h"
#include "Ground.h"
#include "Enemy.h"
#include "Obstacles.h"
#include "Renderer.h"
#include "leveldata.hpp"
#include "Physics.h"
#include <b2_body.h>
#include <b2_circle_shape.h>
#include <b2_fixture.h>
#include <b2_polygon_shape.h>

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

  void CreateLevel1(Renderer& renderer, Physics& physics);

 private:
  std::vector<Entities*> entities;
  Birds* activeBird;
  int score;
  bool levelComplete;
  int currentLevel;

  

  void CreateLevel2(Renderer& renderer, Physics& physics);

  void CreateLevel3(Renderer& renderer, Physics& physics);
};

#endif  // _LEVEL_HPP_
