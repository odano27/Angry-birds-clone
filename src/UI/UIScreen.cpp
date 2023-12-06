#include "UIScreen.h"

UIScreen::UIScreen(const Vector2& globalPosition, IUIManager& manager)
    : _root(std::make_unique<UIElement>(globalPosition)), _manager(manager) {}

void UIScreen::HandleClick(const Vector2& screenPosition) {
  UIClickEvent event{screenPosition, false};
  _root->PropagateClick(event);
}

void UIScreen::Draw(Renderer& renderer) { _root->Draw(renderer); }

void UIScreen::Hide() { _manager.PopScreen(); }

AssetLoader& UIScreen::GetAssets() const { return _manager._assets; }

GameEventBus& UIScreen::GetEventBus() const { return _manager._eventBus; }

const Vector2& UIScreen::GetWindowSize() const { return _manager._windowSize; }
