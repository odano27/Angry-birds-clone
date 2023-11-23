#include "UIText.h"

UIText::UIText(const Vector2& localPosition, const std::string& value,
               const sf::Font& font, int size)
    : UIElement(localPosition),
      _text(std::make_unique<sf::Text>(sf::String(value), font, size)) {}

void UIText::Draw(Renderer& renderer) {
  renderer.DrawText(*_text);
  UIElement::Draw(renderer);
}

void UIText::OnHierarchyChanged() {
  // Update position relative to new parent
  Vector2 globalPosition = GetGlobalPosition();
  _text->setPosition(globalPosition);

  UIElement::OnHierarchyChanged();
}
