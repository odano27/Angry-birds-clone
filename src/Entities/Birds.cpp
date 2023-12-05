#include "Birds.h"

#include <b2_circle_shape.h>
#include <b2_fixture.h>

Birds::Birds(BirdType type, int mouseX, int mouseY, int angle, bool flip,
             Renderer& renderer, Physics& physics, AssetLoader& assets)
    : Entities("Bird"), _type(type) {
  _initAngle = angle;

  switch (type) {
    case BirdType::Red:
      _hitPoints = 100;
      _damage = 10;
      break;

    case BirdType::Yellow:
      _hitPoints = 100;
      _damage = 10;
      break;

    case BirdType::Big_Red:
      _hitPoints = 200;
      _damage = 30;
      break;
  }

  double radius = GetRadius(type);
  Vector2 worldPos = renderer.ScreenToWorld(
      Vector2{static_cast<double>(mouseX), static_cast<double>(mouseY)});

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
  const sf::Texture& texture = assets.GetTexture(GetTextureName(type));
  sf::Vector2u textureSize = texture.getSize();
  SetTexture(texture, {d / textureSize.x * (flip ? -1 : 1), d / textureSize.y});
}

void Birds::Throw(float x, float y, float n) {
  b2Vec2 direction(x, y);
  direction.Normalize();
  b2Body* body = GetBody();
  b2Vec2 impulse = body->GetMass() * n * direction;
  body->ApplyLinearImpulseToCenter(impulse, true);
  body->SetAngularVelocity(-n / 25.0f);
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

const std::string Birds::GetTextureName(BirdType type) {
  switch (type) {
    default:
    case BirdType::Red:
      return "Red";

    case BirdType::Yellow:
      return "Yellow";

    case BirdType::Big_Red:
      return "Big_red";
  }
}

double Birds::GetRadius(BirdType type) {
  switch (type) {
    default:
    case BirdType::Red:
    case BirdType::Yellow:
      return 40.0;

    case BirdType::Big_Red:
      return 50.0;
  }
}
