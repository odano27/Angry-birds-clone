#include "DebugDraw.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "Vector2.h"

DebugDraw::DebugDraw(Renderer& renderer) : _renderer(renderer) {
  SetFlags(b2Draw::e_shapeBit);
}

DebugDraw::~DebugDraw() {}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                            const b2Color& color) {
  sf::ConvexShape shape;
  shape.setPointCount(vertexCount);

  for (int32 i = 0; i < vertexCount; i++) {
    b2Vec2 p = vertices[i];
    Vector2 screenP = _renderer.WorldToScreen({p.x, p.y});
    shape.setPoint(
        i, {static_cast<float>(screenP.x), static_cast<float>(screenP.y)});
  }

  shape.setFillColor(sf::Color::Black);
  shape.setOutlineThickness(1.0f);
  shape.setOutlineColor(GetColor(color));

  _renderer.DrawShape(shape);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                                 const b2Color& color) {
  sf::ConvexShape shape;
  shape.setPointCount(vertexCount);

  for (int32 i = 0; i < vertexCount; i++) {
    b2Vec2 p = vertices[i];
    Vector2 screenP = _renderer.WorldToScreen({p.x, p.y});
    shape.setPoint(
        i, {static_cast<float>(screenP.x), static_cast<float>(screenP.y)});
  }

  shape.setFillColor(GetColor(color));

  _renderer.DrawShape(shape);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius,
                           const b2Color& color) {
  double screenRadius = radius * Renderer::PPU;
  Vector2 screenPosition =
      _renderer.WorldToScreen({center.x, center.y}) - screenRadius;

  sf::CircleShape shape(screenRadius);
  shape.setFillColor(sf::Color::Black);
  shape.setOutlineThickness(1.0f);
  shape.setOutlineColor(GetColor(color));
  shape.setPosition({static_cast<float>(screenPosition.x),
                     static_cast<float>(screenPosition.y)});

  _renderer.DrawShape(shape);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius,
                                const b2Vec2&, const b2Color& color) {
  double screenRadius = radius * Renderer::PPU;
  Vector2 screenPosition =
      _renderer.WorldToScreen({center.x, center.y}) - screenRadius;

  sf::CircleShape shape(screenRadius);
  shape.setFillColor(GetColor(color));
  shape.setPosition({static_cast<float>(screenPosition.x),
                     static_cast<float>(screenPosition.y)});

  // TODO: draw axis line to indicate rotation
  _renderer.DrawShape(shape);
}

void DebugDraw::DrawSegment(const b2Vec2&, const b2Vec2&, const b2Color&) {
  // TODO: implement
}

void DebugDraw::DrawTransform(const b2Transform&) {
  // TODO: implement
}

void DebugDraw::DrawPoint(const b2Vec2&, float, const b2Color&) {
  // TODO: implement
}

sf::Color DebugDraw::GetColor(const b2Color& color) const {
  int r = color.r * 255;
  int g = color.g * 255;
  int b = color.b * 255;
  int a = 200;
  return sf::Color(r, g, b, a);
}
