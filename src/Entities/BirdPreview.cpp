#include "BirdPreview.h"

#include <cmath>

BirdPreview::BirdPreview(BirdType type, int mouseX, int mouseY,
                         AssetLoader& assets)
    : SpriteEntity(Vector2::zero(), Birds::GetTextureName(type), 1.0f, assets) {
  sf::Vector2f size = _sprite->getLocalBounds().getSize();
  double d = Birds::GetRadius(type) * 2;
  _sprite->setScale(Vector2{d / size.x, d / size.y});

  SetPosition(mouseX, mouseY);
}

void BirdPreview::SetPosition(int mouseX, int mouseY) {
  _sprite->setPosition(
      {static_cast<float>(mouseX), static_cast<float>(mouseY)});
}

void BirdPreview::SetRotation(int angle) { _sprite->setRotation(angle); }

void BirdPreview::SetFlipped(bool flipped) {
  if (flipped == _flipped) return;
  _flipped = flipped;

  sf::Vector2f scale = _sprite->getScale();
  _sprite->setScale(std::abs(scale.x) * (flipped ? -1 : 1), scale.y);
}
