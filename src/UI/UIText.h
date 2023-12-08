#pragma once

#include <SFML/Graphics/Text.hpp>
#include <string>

#include "UIElement.h"

class UITextBuilder;

class UIText : public UIElement {
 public:
  static sf::Color GREEN;
  static sf::Color RED;

  friend class UITextBuilder;

  UIText(const Vector2& localPosition, const std::string& value,
         const sf::Font& font, int size = 12);

  void Draw(Renderer& renderer) override;
  void SetText(const std::string& value);
  void SetColor(const sf::Color& color);

 protected:
  void OnHierarchyChanged() override;

 private:
  std::unique_ptr<sf::Text> _text;
};