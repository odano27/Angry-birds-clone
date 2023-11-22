#pragma once

#include <string>

#include "UIElement.h"

class UIText : public UIElement {
 public:
  UIText(const Vector2& localPosition, const std::string& value);

  void Draw(Renderer& renderer) override;

 private:
  std::string _value;
};