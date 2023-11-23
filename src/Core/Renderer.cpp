#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : _window(window) {
  sf::Vector2u size = window.getSize();
  _windowSize = {static_cast<double>(size.x), static_cast<double>(size.y)};
}

void Renderer::DrawShape(const sf::Shape& shape) { _window.draw(shape); }

Vector2 Renderer::ScreenToWorld(const Vector2& screenPosition) const {
  return {screenPosition.x / PPU, (_windowSize.y - screenPosition.y) / PPU};
}

Vector2 Renderer::WorldToScreen(const Vector2& worldPosition) const {
  return {worldPosition.x * PPU, _windowSize.y - (worldPosition.y * PPU)};
}

RenderScope::RenderScope(Renderer& renderer) : _renderer(renderer) {
  renderer._window.clear(sf::Color::Black);
}

RenderScope::~RenderScope() { _renderer._window.display(); }

void Renderer::DrawSprite(const sf::Sprite& sprite) { _window.draw(sprite); }

void Renderer::DrawText(const sf::Text& text) { _window.draw(text); }

Vector2 Renderer::GetWindowSize() const { return _windowSize; }