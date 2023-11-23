#pragma once

#include <SFML/Graphics/Text.hpp>
#include <string>

#include "UIElement.h"

class UITextBuilder;

class UIText : public UIElement {
 public:
  friend class UITextBuilder;

  UIText(const Vector2& localPosition, const std::string& value,
         const sf::Font& font, int size = 12);

  void Draw(Renderer& renderer) override;

 protected:
  void OnHierarchyChanged() override;

 private:
  std::unique_ptr<sf::Text> _text;
};