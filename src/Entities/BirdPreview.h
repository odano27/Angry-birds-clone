#pragma once

#include "Birds.h"
#include "SpriteEntity.h"

class BirdPreview : public SpriteEntity {
 public:
  BirdPreview(BirdType type, int mouseX, int mouseY, AssetLoader& assets);

  void SetPosition(int mouseX, int mouseY);
  void SetRotation(int angle);
  void SetFlipped(bool flipped);

 private:
  bool _flipped;
};
