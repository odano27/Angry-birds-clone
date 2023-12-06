#include "UIImage.h"

UIImage::UIImage(const Vector2& localPosition) : UIElement(localPosition) {}

void UIImage::Draw(Renderer& renderer) {
  // Draw self first
  if (_shape != nullptr) renderer.DrawShape(*_shape);
  if (_sprite != nullptr) renderer.DrawSprite(*_sprite);
  // Then draw childs
  UIElement::Draw(renderer);
}

void UIImage::SetScale(const Vector2& scale) {
  if (_shape != nullptr) _shape->setScale(scale);
  if (_sprite != nullptr) _sprite->setScale(scale);
}

void UIImage::OnHierarchyChanged() {
  // Update position relative to new parent
  Vector2 globalPosition = GetGlobalPosition();
  if (_shape != nullptr) _shape->setPosition(globalPosition);
  if (_sprite != nullptr) _sprite->setPosition(globalPosition);

  UIElement::OnHierarchyChanged();
}

bool UIImage::CanReceiveClick(const Vector2& screenPosition) const {
  if (_shape != nullptr)
    return _shape->getGlobalBounds().contains(screenPosition);
  if (_sprite != nullptr)
    return _sprite->getGlobalBounds().contains(screenPosition);
  return false;
}
