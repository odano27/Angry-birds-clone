#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "UIElement.h"

class UIButtonBuilder;

class UIButton : public UIElement {
 public:
  friend class UIButtonBuilder;

  UIButton(const Vector2& localPosition);

 protected:
  bool TryProcessClick(UIClickEvent& event) override;

 private:
  std::function<void()> _onClick;
};
