#pragma once

#include "UIElement.h"

class UIScreen {
 public:
  UIScreen(const Vector2& globalPosition);
  virtual ~UIScreen() {}

  void HandleClick(const Vector2& screenPosition);
  void Draw(Renderer& renderer);

 protected:
  std::unique_ptr<UIElement> _root;
};
