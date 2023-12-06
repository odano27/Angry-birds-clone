#pragma once

#include <SFML/Graphics.hpp>

#include "UIElement.h"

class UIImageBuilder;

class UIImage : public UIElement {
 public:
  friend class UIImageBuilder;

  UIImage(const Vector2& localPosition);

  void Draw(Renderer& renderer) override;

 protected:
  void OnHierarchyChanged() override;
  bool CanReceiveClick(const Vector2& screenPosition) const override;

 private:
  std::unique_ptr<sf::Shape> _shape;
  std::unique_ptr<sf::Sprite> _sprite;
};
