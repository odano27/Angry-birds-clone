#include "SpriteEntity.h"

SpriteEntity::SpriteEntity(const Vector2& screenPos,
                           const std::string& textureName, float scale,
                           AssetLoader& assets)
    : Entities(textureName) {
  SetTexture(assets.GetTexture(textureName), Vector2::one() * scale);

  Vector2 position = screenPos + _sprite->getGlobalBounds().getSize() / 2.0f;
  _sprite->setPosition(position);
}

void SpriteEntity::Draw(Renderer& renderer, double) {
  renderer.DrawSprite(*_sprite);
}
