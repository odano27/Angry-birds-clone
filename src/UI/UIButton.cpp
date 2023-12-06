#include "UIButton.h"

#include "UIImage.h"

UIButton::UIButton(const Vector2& localPosition) : UIElement(localPosition) {}

void UIButton::SetScale(const Vector2& scale) {
  UIImage& image = static_cast<UIImage&>(GetChild(0));
  image.SetScale(scale);
}

bool UIButton::TryProcessClick(UIClickEvent&) {
  if (!_onClick) return false;
  _onClick();
  return true;
}
