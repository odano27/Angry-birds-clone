#include "Slingshot.h"

Slingshot::Slingshot(const Vector2& screenPos, AssetLoader& assets)
    : SpriteEntity(screenPos, "Slingshot", 0.5f, assets) {}

bool Slingshot::IsPressed(float mouseX, float mouseY) const {
  return _sprite->getGlobalBounds().contains({mouseX, mouseY});
}

sf::Vector2f Slingshot::GetSpawnPosition() const {
  sf::Vector2 position = _sprite->getPosition();
  // Offset a bit closer to top of the slingshot
  position.y -= 50.0f;
  return position;
}
