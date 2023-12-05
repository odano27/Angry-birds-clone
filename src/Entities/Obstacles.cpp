#include "Obstacles.h"

#include <b2_fixture.h>
#include <b2_polygon_shape.h>

Obstacles::Obstacles(ObstacleType type, const Vector2& screenPos,
                     Renderer& renderer, Physics& physics, AssetLoader& assets)
    : Entities("Obstacle") {
  _hitPoints = 50;
  _damage = 20;

  Vector2 size;
  std::string textureName;
  switch (type) {
    case ObstacleType::Plank_ver:
      size = {35.0, 110.0};
      textureName = "Plank";
      break;

    case ObstacleType::Plank_hor:
      size = {110.0, 35.0};
      textureName = "Plank_h";
      break;
  }

  Vector2 worldPos = renderer.ScreenToWorld(screenPos + size / 2);

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(worldPos.x, worldPos.y);

  b2PolygonShape shape;
  shape.SetAsBox((size.x / 2.0) / Renderer::PPU,
                 ((size.y / 2.0) / Renderer::PPU));

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.7f;

  b2Body* body = physics.CreateBody(&bodyDef);
  body->CreateFixture(&fixtureDef);
  SetBody(body);

  const sf::Texture& texture = assets.GetTexture(textureName);
  sf::Vector2u textureSize = texture.getSize();
  SetTexture(texture, {size.x / textureSize.x, size.y / textureSize.y});
}