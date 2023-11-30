#pragma once

#include <b2_world.h>

#include "DebugDraw.h"
#include "GameEvent.h"

class Physics : public IGameEventHandler {
 public:
  Physics(DebugDraw* debugDraw);
  ~Physics();

  void FixedUpdate(double fixedDeltaTime);
  void DrawDebug();

  b2Body* CreateBody(const b2BodyDef* bodyDef);

  void HandleGameEvent(const GameEvent& event) override;

 private:
  b2World* _world;
  DebugDraw* _debugDraw;

  void DestroyBody(b2Body* body);
};