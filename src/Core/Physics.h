#pragma once

#include <b2_world.h>

#include "ContactListener.h"
#include "DebugDraw.h"
#include "Renderer.h"

class Physics {
 public:
  Physics(Renderer& renderer);

  void FixedUpdate(double fixedDeltaTime);
  void DrawDebug();
  void SetCollisionsEnabled(bool enabled);

  b2Body* CreateBody(const b2BodyDef* bodyDef);
  void DestroyBody(b2Body* body);

 private:
  DebugDraw _debugDraw;
  ContactListener _contactListener;

  std::unique_ptr<b2World> _world;
};