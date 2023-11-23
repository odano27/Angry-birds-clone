#include "UIScreen.h"

UIScreen::UIScreen(const Vector2& globalPosition, AssetLoader& assets)
    : _root(std::make_unique<UIElement>(globalPosition)), _assets(assets) {}

void UIScreen::HandleClick(const Vector2& screenPosition) {
  UIClickEvent event{screenPosition, false};
  _root->PropagateClick(event);
}

void UIScreen::Draw(Renderer& renderer) { _root->Draw(renderer); }
