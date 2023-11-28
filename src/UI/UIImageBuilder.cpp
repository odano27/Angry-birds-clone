#include "UIImageBuilder.h"

UIImageBuilder::UIImageBuilder(const Vector2& localPosition)
    : _image(std::make_unique<UIImage>(localPosition)) {}

UIImageBuilder& UIImageBuilder::WithRect(float width, float height) {
  _image->_shape =
      std::make_unique<sf::RectangleShape>(sf::Vector2(width, height));
  return *this;
}

UIImageBuilder& UIImageBuilder::WithColor(const sf::Color& color) {
  _image->_shape->setFillColor(color);
  return *this;
}

UIImageBuilder& UIImageBuilder::WithOriginAtCenter() {
  sf::Vector2f size = _image->_shape->getLocalBounds().getSize();
  _image->_shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
  return *this;
}

std::unique_ptr<UIImage> UIImageBuilder::Build() { return std::move(_image); }
