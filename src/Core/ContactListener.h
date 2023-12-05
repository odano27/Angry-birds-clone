#pragma once

#include <b2_contact.h>
#include <b2_world_callbacks.h>

class ContactListener : public b2ContactListener {
 public:
  ContactListener();

  void SetCollisionsEnabled(bool enabled);

  void BeginContact(b2Contact* contact) override;

 private:
  bool _collisionsEnabled;
};
