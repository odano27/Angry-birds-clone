#pragma once

#include "AssetLoader.h"
#include "Entities.h"

class SpriteEntity : public Entities {
 public:
  SpriteEntity(const Vector2& screenPos, const std::string& textureName,
               float scale, AssetLoader& assets);

  void Draw(Renderer& renderer, double t) override;
};
