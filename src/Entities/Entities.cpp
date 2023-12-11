#include "Entities.h"

#include <cmath>

Entities::Entities(const std::string& name) : _name(name) {
  _body = nullptr;
  _shape = nullptr;
  _sprite = nullptr;

  _initAngle = 0;
  _position = Vector2::zero();
  _prevPosition = Vector2::zero();

  _hitPoints = 999999999;
  _damage = 0;
  _isDestroyed = false;
  _soundBuffer[0].loadFromFile("src/Assets/Sounds/Oink.wav");
  _soundBuffer[1].loadFromFile("src/Assets/Sounds/Wood_destroyed.wav");
  _Sounds[0].setBuffer(_soundBuffer[0]);
  _Sounds[1].setBuffer(_soundBuffer[1]);

}

void Entities::SetBody(b2Body* body) {
  _body = body;

  // Keep a pointer to this entity in body's userData
  // This way we can access entity when we only have body (e.g. in physics)
  b2BodyUserData& userData = _body->GetUserData();
  userData.pointer = reinterpret_cast<uintptr_t>(this);
}

void Entities::SetTexture(const sf::Texture& texture, const Vector2& scale) {
  _sprite = std::make_unique<sf::Sprite>(texture);
  _sprite->setScale(scale);

  // Set origin to center as body position is center of the body
  sf::Vector2f size = _sprite->getLocalBounds().getSize();
  _sprite->setOrigin(size / 2.0f);
}

void Entities::SetTextureRect(const sf::IntRect& rect, bool setOriginToCenter) {
  if (_sprite == nullptr) return;
  _sprite->setTextureRect(rect);

  if (!setOriginToCenter) return;
  sf::Vector2i size = rect.getSize();
  _sprite->setOrigin(size.x / 2, size.y / 2);
}

void Entities::SetRectShape(const Vector2& size) {
  _shape = std::make_unique<sf::RectangleShape>(size);
  _sprite->setOrigin(size / 2.0f);
}

void Entities::SetCirceShape(int radius) {
  _shape = std::make_unique<sf::CircleShape>(radius);
  _sprite->setOrigin(radius, radius);
}

void Entities::DestroyBody(Physics& physics) {
  if (_body == nullptr) return;
  physics.DestroyBody(_body);
  _body = nullptr;
}

void Entities::Draw(Renderer& renderer, double t) {
  if (_body == nullptr || (_shape == nullptr && _sprite == nullptr)) return;

  // Body position is in physics world space
  b2Vec2 bodyPosition = _body->GetPosition();
  // Body angle is in radians
  float bodyAngle = _body->GetAngle() * (180 / b2_pi) * -1;

  _position = renderer.WorldToScreen({bodyPosition.x, bodyPosition.y});
  // Interpolated position in current render frame
  Vector2 framePosition = Vector2::lerp(_prevPosition, _position, t);
  _prevPosition = _position;

  sf::Vector2f size;
  if (_sprite != nullptr) {
    size = _sprite->getGlobalBounds().getSize();

    _sprite->setPosition(framePosition.x, framePosition.y);
    _sprite->setRotation(_initAngle + bodyAngle);

    renderer.DrawSprite(*_sprite);
  } else if (_shape != nullptr) {
    size = _shape->getGlobalBounds().getSize();

    _shape->setPosition(framePosition.x, framePosition.y);
    _shape->setRotation(_initAngle + bodyAngle);

    renderer.DrawShape(*_shape);
  }

  // Check if entity bounds is out of view bounds
  Vector2 topLeft = framePosition - size / 2.0f;
  Vector2 bottomRight = framePosition + size / 2.0f;
  const Vector2 windowSize = renderer.GetWindowSize();
  if (bottomRight.x < 0 || bottomRight.y < 0 || topLeft.x > windowSize.x ||
      topLeft.y > windowSize.y) {
    _isDestroyed = true;
  }
}

void Entities::CollideWith(Entities* other) {
  if (this->isEnemy()) {
    _Sounds[0].play();
  }
  _hitPoints -= other->GetDamage();
  if (_hitPoints <= 0) {
    if (!this->isEnemy() && !this ->IsBird()) {
      _Sounds[1].play();
    }
    _isDestroyed = true;
  }
}

bool Entities::IsDestroyed() const { return _isDestroyed; }

bool Entities::CanCollide() const { return !_isDestroyed && _damage > 0; }

b2Body* Entities::GetBody() const { return _body; }

int Entities::GetDamage() const { return _damage; }