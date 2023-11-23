#include "UIButton.h"

UIButton::UIButton(const Vector2& localPosition) : UIElement(localPosition) {}

bool UIButton::TryProcessClick(UIClickEvent&) {
  if (_onClick == nullptr) return false;
  _onClick();
  return true;
}
