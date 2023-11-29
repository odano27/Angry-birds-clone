#include "UIScreen.h"

UIScreen::UIScreen(const Vector2& globalPosition, IUIManager& manager)
    : _root(std::make_unique<UIElement>(globalPosition)), _manager(manager) {}

void UIScreen::HandleClick(const Vector2& screenPosition) {
  UIClickEvent event{screenPosition, false};
  _root->PropagateClick(event);
}

void UIScreen::Draw(Renderer& renderer) { _root->Draw(renderer); }

void UIScreen::Hide() { _manager.PopScreen(); }

AssetLoader& UIScreen::GetAssets() { return _manager._assets; }
