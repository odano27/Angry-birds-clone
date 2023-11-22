#include "UIText.h"

UIText::UIText(const Vector2& localPosition, const std::string& value)
    : UIElement(localPosition), _value(value) {}

void UIText::Draw(Renderer& renderer) {
  // TODO: draw text

  UIElement::Draw(renderer);
}
