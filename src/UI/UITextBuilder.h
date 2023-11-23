#pragma once

#include <SFML/Graphics/Font.hpp>

#include "UIText.h"

class UITextBuilder {
 public:
  UITextBuilder(const Vector2& localPosition, const std::string& value,
                const sf::Font& font, int size = 12);

  UITextBuilder& WithFont(const sf::Font& font);
  UITextBuilder& WithSize(int size);
  UITextBuilder& WithColor(const sf::Color& color);
  UITextBuilder& WithOriginAtCenter();
  std::unique_ptr<UIText> Build();

 private:
  std::unique_ptr<UIText> _text;
};
