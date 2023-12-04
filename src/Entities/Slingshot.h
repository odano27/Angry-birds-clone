#pragma once

#include "SpriteEntity.h"

class Slingshot : public SpriteEntity {
 public:
  Slingshot(const Vector2& screenPos, AssetLoader& assets);

  bool IsPressed(float mouseX, float mouseY) const;

  sf::Vector2f GetSpawnPosition() const;
};
