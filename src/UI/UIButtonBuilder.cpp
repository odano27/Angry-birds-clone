#include "UIButtonBuilder.h"

UIButtonBuilder::UIButtonBuilder(const Vector2& localPosition)
    : _button(std::make_unique<UIButton>(localPosition)),
      _width(0),
      _height(0) {}

UIButtonBuilder& UIButtonBuilder::WithRect(float width, float height,
                                           const sf::Color& color) {
  _width = width;
  _height = height;
  _button->AddChild(UIImageBuilder({0.0, 0.0})
                        .WithRect(width, height)
                        .WithColor(color)
                        .Build());
  return *this;
}

UIButtonBuilder& UIButtonBuilder::WithText(const std::string& value,
                                           const sf::Font& font, int size,
                                           const sf::Color& color) {
  _button->AddChild(
      UITextBuilder({_width / 2.0, _height / 2.0}, value, font, size)
          .WithColor(color)
          .WithOriginAtCenter()
          .Build());
  return *this;
}

UIButtonBuilder& UIButtonBuilder::WithClickHandler(void (*onClick)()) {
  _button->_onClick = onClick;
  return *this;
}

std::unique_ptr<UIButton> UIButtonBuilder::Build() {
  return std::move(_button);
}
