#pragma once

#include <SFML/Graphics.hpp>

#include "UIElement.h"

class UIButton : public UIElement {
 public:
  UIButton(const Vector2& localPosition, float width, float height,
           const sf::Color& color, void (*onClick)());

 protected:
  bool TryProcessClick(UIClickEvent& event) override;

 private:
  void (*_onClick)();
};
