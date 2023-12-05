#include "ContactListener.h"

#include <b2_body.h>

#include "Entities.h"

ContactListener::ContactListener() { _collisionsEnabled = true; }

void ContactListener::SetCollisionsEnabled(bool enabled) {
  _collisionsEnabled = enabled;
}

void ContactListener::BeginContact(b2Contact* contact) {
  if (!_collisionsEnabled) return;

  b2BodyUserData& userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
  Entities* entityA = reinterpret_cast<Entities*>(userDataA.pointer);

  b2BodyUserData& userDataB = contact->GetFixtureB()->GetBody()->GetUserData();
  Entities* entityB = reinterpret_cast<Entities*>(userDataB.pointer);

  if (entityA->CanCollide() && entityB->CanCollide()) {
    entityA->CollideWith(entityB);
    entityB->CollideWith(entityA);
  }
}
