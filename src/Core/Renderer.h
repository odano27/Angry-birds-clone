#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"

class RenderScope;

class Renderer {
 public:
  static constexpr double PPU = 30.0;

  friend class RenderScope;

  Renderer(sf::RenderWindow& window);

  void DrawShape(const sf::Shape& shape);

  Vector2 ScreenToWorld(const Vector2& screenPosition) const;
  Vector2 WorldToScreen(const Vector2& worldPosition) const;

 private:
  sf::RenderWindow& _window;
  Vector2 _windowSize;
};

class RenderScope {
 public:
  RenderScope(Renderer& renderer);
  ~RenderScope();

 private:
  Renderer& _renderer;
};