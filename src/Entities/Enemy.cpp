#include "Enemy.h"

#include <b2_circle_shape.h>
#include <b2_fixture.h>

Enemy::Enemy(EnemyType type, const Vector2& screenPos, Renderer& renderer,
             Physics& physics, AssetLoader& assets)
    : Entities("Enemy"), _type(type) {
  std::string textureName;
  switch (_type) {
    case EnemyType::Pig:
      _hitPoints = 100;
      _damage = 10;
      _instakillRequirement = 30;
      textureName = "Pig";
      break;

    case EnemyType::Pig_Mustache:
      _hitPoints = 150;
      _damage = 10;
      _instakillRequirement = 40;
      textureName = "Pig_Mustache";
      break;

    case EnemyType::Pig_King:
      _hitPoints = 200;
      _damage = 12;
      _instakillRequirement = 50;
      textureName = "Pig_King";
      break;
  }

  const double radius = 30.0;
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

void Enemy::CollideWith(Entities* other) {
  if (other->IsBird()) {
    if (other->GetDamage() >= _instakillRequirement) {
      _hitPoints = -1;
    } else {
      _hitPoints -= other->GetDamage();
    }
  }
}