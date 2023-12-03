#include "Ground.h"

#include <b2_polygon_shape.h>

Ground::Ground(Renderer& renderer, Physics& physics, AssetLoader& assets)
    : Entities("Ground") {
  // ground fill the entire bottom of the window
  Vector2 windowSize = renderer.GetWindowSize();
  Vector2 size = {windowSize.x, 200.0};

  Vector2 screenPos = Vector2{0.0, windowSize.y - size.y};
  Vector2 worldPos = renderer.ScreenToWorld(screenPos + (size / 2));

  b2BodyDef bodyDef;
  bodyDef.position.Set(worldPos.x, worldPos.y);

  b2PolygonShape shape;
  shape.SetAsBox((size.x / 2.0) / Renderer::PPU,
                 ((size.y / 2.0) / Renderer::PPU));

  b2Body* body = physics.CreateBody(&bodyDef);
  body->CreateFixture(&shape, 0.0f);
  SetBody(body);

  SetTexture(assets.GetTexture("Grass", true), Vector2::one());
  SetTextureRect(sf::IntRect(0, 0, size.x, size.y), true);
}
