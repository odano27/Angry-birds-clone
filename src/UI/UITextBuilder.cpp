#include "UITextBuilder.h"

UITextBuilder::UITextBuilder(const Vector2& localPosition,
                             const std::string& value, const sf::Font& font,
                             int size)
    : _text(std::make_unique<UIText>(localPosition, value, font, size)) {}

UITextBuilder& UITextBuilder::WithFont(const sf::Font& font) {
  _text->_text->setFont(font);
  return *this;
}

UITextBuilder& UITextBuilder::WithSize(int size) {
  _text->_text->setCharacterSize(size);
  return *this;
}

UITextBuilder& UITextBuilder::WithColor(const sf::Color& color) {
  _text->_text->setFillColor(color);

  return *this;
}

UITextBuilder& UITextBuilder::WithOutline(const sf::Color& color,
                                          float thickness) {
  _text->_text->setOutlineColor(color);
  _text->_text->setOutlineThickness(thickness);
  return *this;
}

UITextBuilder& UITextBuilder::WithOriginAtCenter() {
  sf::Vector2f size = _text->_text->getLocalBounds().getSize();
  _text->_text->setOrigin(size.x / 2.0f, size.y / 2.0f);
  return *this;
}

std::unique_ptr<UIText> UITextBuilder::Build() { return std::move(_text); }
