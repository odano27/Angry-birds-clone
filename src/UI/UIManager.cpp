#include "UIManager.h"

#include "HUD.h"
#include "MainMenu.h"

UIManager::UIManager(AssetLoader& assets, Vector2 windowSize)
    : IUIManager(assets, windowSize) {}

UIScreen& UIManager::Show(UIScreenType screenType) {
  if (_screens.empty() || _screens.back()->GetType() != screenType)
    _screens.emplace_back(CreateScreen(screenType));
  return *_screens.back();
}

void UIManager::Draw(Renderer& renderer) {
  // Draw all screens from lower to top
  for (auto it = _screens.begin(); it != _screens.end(); it++)
    (*it)->Draw(renderer);
}

void UIManager::HandleInputEvent(const sf::Event& event) {
  if (_screens.empty() || event.type != sf::Event::MouseButtonPressed) return;
  Vector2 screenPosition{static_cast<double>(event.mouseButton.x),
                         static_cast<double>(event.mouseButton.y)};
  // Only top screen receives input
  _screens.back()->HandleClick(screenPosition);
}

void UIManager::PopScreen() { _screens.pop_back(); }

std::unique_ptr<UIScreen> UIManager::CreateScreen(UIScreenType screenType) {
  switch (screenType) {
    case UIScreenType::MainMenu:
      return std::make_unique<MainMenu>(*this);

    case UIScreenType::HUD:
      return std::make_unique<HUD>(*this);

    default:
      return nullptr;
  }
}