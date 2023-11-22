#include "UIImage.h"

UIImage::UIImage(const Vector2& localPosition) : UIElement(localPosition) {}

void UIImage::Draw(Renderer& renderer) {
  // Draw self first
  if (_shape != nullptr) renderer.DrawShape(*_shape);
  // Then draw childs
  UIElement::Draw(renderer);
}

void UIImage::OnHierarchyChanged() {
  // Update position relative to new parent
  Vector2 globalPosition = GetGlobalPosition();
  if (_shape != nullptr) _shape->setPosition(globalPosition);

  UIElement::OnHierarchyChanged();
}

bool UIImage::CanReceiveClick(const Vector2& screenPosition) const {
  return _shape != nullptr &&
         _shape->getGlobalBounds().contains(screenPosition);
}
