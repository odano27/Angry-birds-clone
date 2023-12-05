#include "Physics.h"

#include <b2_common.h>

const int32 _velocityIterations = 12;
const int32 _positionIterations = 15;

Physics::Physics(Renderer& renderer)
    : _debugDraw(DebugDraw(renderer)), _contactListener(ContactListener()) {
  b2Vec2 gravity(0.0f, -10.0f);
  _world = std::make_unique<b2World>(gravity);
  _world->SetDebugDraw(&_debugDraw);
  _world->SetContactListener(&_contactListener);
}

void Physics::FixedUpdate(double fixedDeltaTime) {
  _world->Step(fixedDeltaTime, _velocityIterations, _positionIterations);
}

void Physics::DrawDebug() { _world->DebugDraw(); }

void Physics::SetCollisionsEnabled(bool enabled) {
  _contactListener.SetCollisionsEnabled(enabled);
}

b2Body* Physics::CreateBody(const b2BodyDef* bodyDef) {
  return _world->CreateBody(bodyDef);
}

void Physics::DestroyBody(b2Body* body) { _world->DestroyBody(body); }
