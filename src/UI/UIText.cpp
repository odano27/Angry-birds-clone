#include "UIText.h"

sf::Color UIText::GREEN = sf::Color(188, 236, 28);
sf::Color UIText::RED = sf::Color(215, 70, 59);

UIText::UIText(const Vector2& localPosition, const std::string& value,
               const sf::Font& font, int size)
    : UIElement(localPosition),
      _text(std::make_unique<sf::Text>(sf::String(value), font, size)) {}

void UIText::Draw(Renderer& renderer) {
  renderer.DrawText(*_text);
  UIElement::Draw(renderer);
}

void UIText::SetText(const std::string& value) {
  const sf::Font* font = _text->getFont();
  int size = _text->getCharacterSize();
  sf::Color color = _text->getFillColor();
  sf::Color outlineColor = _text->getOutlineColor();
  float outlineThickness = _text->getOutlineThickness();
  sf::Vector2f origin = _text->getOrigin();
  sf::Vector2f position = _text->getPosition();

  _text.reset(new sf::Text(sf::String(value), *font, size));
  _text->setFillColor(color);
  _text->setOutlineColor(outlineColor);
  _text->setOutlineThickness(outlineThickness);
  _text->setOrigin(origin);
  _text->setPosition(position);
}

void UIText::SetColor(const sf::Color& color) { _text->setFillColor(color); }

void UIText::OnHierarchyChanged() {
  // Update position relative to new parent
  Vector2 globalPosition = GetGlobalPosition();
  _text->setPosition(globalPosition);

  UIElement::OnHierarchyChanged();
}
