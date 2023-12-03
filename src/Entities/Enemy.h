#ifndef ENEMY_H
#define ENEMY_H

#include "AssetLoader.h"
#include "Entities.h"

enum class EnemyType {
  Pig,
  Pig_Mustache,
  Pig_King,
};

class Enemy : public Entities {
 public:
  Enemy(EnemyType type, const Vector2& screenPos, Renderer& renderer,
        Physics& physics, AssetLoader& assets);

  void CollideWith(Entities* other) override;

  bool isEnemy() const override {
    return true;
  }  // override to be true, default false

 private:
  EnemyType _type;
  int _instakillRequirement;  // pigs get instakilled when hit with birds with
                              // enough damage
};

#endif  // ENEMY_H
