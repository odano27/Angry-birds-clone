#include "Physics.h"

#include <b2_common.h>

const int32 _velocityIterations = 15;
const int32 _positionIterations = 15;

Physics::Physics(DebugDraw* debugDraw) : _debugDraw(debugDraw) {
  b2Vec2 gravity(0.0f, -10.0f);
  _world = new b2World(gravity);
  _world->SetDebugDraw(debugDraw);
}

Physics::~Physics() {
  delete _world;
  delete _debugDraw;
}

void Physics::FixedUpdate(double fixedDeltaTime) {
  _world->Step(fixedDeltaTime, _velocityIterations, _positionIterations);
}

void Physics::DrawDebug() { _world->DebugDraw(); }

b2Body* Physics::CreateBody(const b2BodyDef* bodyDef) {
  return _world->CreateBody(bodyDef);
}

void Physics::HandleGameEvent(const GameEvent& event) {
  if (event.type == GameEvent::DestroyBody) {
    DestroyBody(event.destroyBody.body);
  }
}

void Physics::DestroyBody(b2Body* body) { _world->DestroyBody(body); }
