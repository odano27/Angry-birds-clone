#include "UIText.h"

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
  sf::Vector2f origin = _text->getOrigin();
  sf::Vector2f position = _text->getPosition();

  _text.reset(new sf::Text(sf::String(value), *font, size));
  _text->setFillColor(color);
  _text->setOrigin(origin);
  _text->setPosition(position);
}

void UIText::OnHierarchyChanged() {
  // Update position relative to new parent
  Vector2 globalPosition = GetGlobalPosition();
  _text->setPosition(globalPosition);

  UIElement::OnHierarchyChanged();
}
