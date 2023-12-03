#include "Birds.h"

#include <b2_circle_shape.h>
#include <b2_fixture.h>

Birds::Birds(BirdType type, const Vector2& screenPos, Renderer& renderer,
             Physics& physics, AssetLoader& assets)
    : Entities("Bird"), _type(type) {
  double radius = 40.0;
  std::string textureName;
  switch (_type) {
    case BirdType::Red:
      _hitPoints = 100;
      _damage = 10;
      textureName = "Red";
      break;

    case BirdType::Yellow:
      _hitPoints = 100;
      _damage = 10;
      textureName = "Yellow";
      break;

    case BirdType::Big_Red:
      _hitPoints = 200;
      _damage = 30;
      radius = 50.0;
      textureName = "Big_red";
      break;
  }

  Vector2 worldPos = renderer.ScreenToWorld(screenPos + radius);

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(worldPos.x, worldPos.y);

  b2CircleShape shape;
  shape.m_radius = radius / Renderer::PPU;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  b2Body* body = physics.CreateBody(&bodyDef);
  body->CreateFixture(&fixtureDef);

  SetBody(body);

  double d = radius * 2;
  const sf::Texture& texture = assets.GetTexture(textureName);
  sf::Vector2u textureSize = texture.getSize();
  SetTexture(texture, {d / textureSize.x, d / textureSize.y});
}

void Birds::ApplyForce(float x, float y, float n) {
  b2Vec2 direction(x, y);
  direction.Normalize();
  b2Vec2 force = n * direction;
  GetBody()->ApplyForceToCenter(force, true);
}

void Birds::ability(Vector2 mouseLocation) {
  switch (_type) {
    case BirdType::Red:  // nothing
      break;

    case BirdType::Big_Red:  // nothing
      break;

    case BirdType::Yellow:
      float origSpeed = this->GetBody()->GetLinearVelocity().Length();
      b2Vec2 direction(mouseLocation.x - this->GetBody()->GetPosition().x,
                       mouseLocation.y - this->GetBody()->GetPosition().y);
      float length =
          std::sqrt(direction.x * direction.x + direction.y * direction.y);
      b2Vec2 normalizedDirection =
          b2Vec2(direction.x / length, direction.y / length);
      float speed = origSpeed * 3;  // replace with desired speed
      b2Vec2 velocity = speed * normalizedDirection;
      this->GetBody()->SetLinearVelocity(velocity);
      break;
  }
}

int Birds::GetDamage() const {
  return _damage * this->GetBody()->GetLinearVelocity().Length();
}