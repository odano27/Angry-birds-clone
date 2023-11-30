#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <b2_body.h>
#include <b2_circle_shape.h>
#include <b2_fixture.h>
#include <b2_polygon_shape.h>

#include <iostream>
#include <vector>

#include "Birds.h"
#include "Enemy.h"
#include "Entities.h"
#include "Ground.h"
#include "Obstacles.h"
#include "Physics.h"
#include "Renderer.h"
#include "leveldata.hpp"

class Level {
 public:
  Level(GameEventBus& eventBus);
  ~Level();

  void loadLevel(LevelData& data);
  bool isCompleted() const;
  int calculateScore();

  void Draw(Renderer& renderer, double t);

  void AddEntity(Entities* entity);

  void SwitchToLevel(int levelNumber);

  void CreateLevel1(Renderer& renderer, Physics& physics);

 private:
  GameEventBus& _eventBus;
  std::vector<Entities*> entities;
  Birds* activeBird;
  int score;
  bool levelComplete;
  int currentLevel;

  void CreateLevel2(Renderer& renderer, Physics& physics);

  void CreateLevel3(Renderer& renderer, Physics& physics);
};

#endif  // _LEVEL_HPP_
