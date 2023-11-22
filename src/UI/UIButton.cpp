#include "UIButton.h"

#include "UIImageBuilder.h"

UIButton::UIButton(const Vector2& localPosition, float width, float height,
                   const sf::Color& color, void (*onClick)())
    : UIElement(localPosition), _onClick(onClick) {
  AddChild(UIImageBuilder({0.0, 0.0})
               .WithRect(width, height)
               .WithColor(color)
               .Build());

  // TODO: add text child
}

bool UIButton::TryProcessClick(UIClickEvent&) {
  _onClick();
  return true;
}
