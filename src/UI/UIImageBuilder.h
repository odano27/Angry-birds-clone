#pragma once

#include "UIImage.h"

class UIImageBuilder {
 public:
  UIImageBuilder(const Vector2& localPosition);

  UIImageBuilder& WithRect(float width, float height);
  UIImageBuilder& WithColor(const sf::Color& color);
  UIImageBuilder& WithTexture(const sf::Texture& texture, const Vector2& scale = Vector2::one());
  UIImageBuilder& WithOriginAtCenter();
  std::unique_ptr<UIImage> Build();

 private:
  std::unique_ptr<UIImage> _image;
};
