#include "UIButtonBuilder.h"

UIButtonBuilder::UIButtonBuilder(const Vector2& localPosition,
                                 bool originAtCenter)
    : _button(std::make_unique<UIButton>(localPosition)),
      _originAtCenter(originAtCenter),
      _width(0),
      _height(0) {}

UIButtonBuilder& UIButtonBuilder::WithRect(float width, float height,
                                           const sf::Color& color) {
  _width = width;
  _height = height;

  UIImageBuilder builder({0.0, 0.0});
  builder.WithRect(width, height);
  builder.WithColor(color);
  if (_originAtCenter) builder.WithOriginAtCenter();

  _button->AddChild(builder.Build());
  return *this;
}

UIButtonBuilder& UIButtonBuilder::WithText(const std::string& value,
                                           const sf::Font& font, int size,
                                           const sf::Color& color) {
  UITextBuilder builder({0.0, 0.0}, value, font, size);
  builder.WithColor(color);
  if (_originAtCenter) builder.WithOriginAtCenter();

  _button->AddChild(builder.Build());
  return *this;
}

UIButtonBuilder& UIButtonBuilder::WithClickHandler(
    std::function<void()> onClick) {
  _button->_onClick = onClick;
  return *this;
}

std::unique_ptr<UIButton> UIButtonBuilder::Build() {
  return std::move(_button);
}
