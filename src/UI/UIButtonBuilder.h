#pragma once

#include "UIButton.h"
#include "UIImageBuilder.h"
#include "UITextBuilder.h"

class UIButtonBuilder {
 public:
  UIButtonBuilder(const Vector2& localPosition, bool originAtCenter = false);

  UIButtonBuilder& WithRect(float width, float height,
                            const sf::Color& color = sf::Color::White);
  UIButtonBuilder& WithText(const std::string& value, const sf::Font& font,
                            int size = 18,
                            const sf::Color& color = sf::Color::Black);
  UIButtonBuilder& WithClickHandler(void (*onClick)());
  std::unique_ptr<UIButton> Build();

 private:
  std::unique_ptr<UIButton> _button;
  bool _originAtCenter;
  float _width;
  float _height;
};
