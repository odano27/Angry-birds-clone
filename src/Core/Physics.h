#pragma once

#include <b2_world.h>

#include "DebugDraw.h"

class Physics {
 public:
  Physics(DebugDraw* debugDraw);
  ~Physics();

  void FixedUpdate(double fixedDeltaTime);
  void DrawDebug();

  b2Body* CreateBody(const b2BodyDef* bodyDef);
  void DestroyBody(b2Body* body);

 private:
  b2World* _world;
  DebugDraw* _debugDraw;
};