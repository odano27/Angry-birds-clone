#include "UIManager.h"

#include "CompletedMenu.h"
#include "HUD.h"
#include "MainMenu.h"

UIManager::UIManager(GameEventBus& eventBus, AssetLoader& assets,
                     Vector2 windowSize)
    : IUIManager(eventBus, assets, windowSize) {}

UIScreen& UIManager::Show(UIScreenType screenType, void* data) {
  if (_screens.empty() || _screens.back()->GetType() != screenType)
    _screens.emplace_back(CreateScreen(screenType, data));
  return *_screens.back();
}

UIScreen* UIManager::Get(UIScreenType screenType) const {
  for (auto& screen : _screens) {
    if (screen->GetType() == screenType) return screen.get();
  }
  return nullptr;
}

void UIManager::Draw(Renderer& renderer) {
  // Draw all screens from lower to top
  for (auto it = _screens.begin(); it != _screens.end(); it++)
    (*it)->Draw(renderer);
}

void UIManager::HideAll() {
  while (!_screens.empty()) PopScreen();
}

void UIManager::HandleInputEvent(const sf::Event& event) {
  if (_screens.empty() || event.type != sf::Event::MouseButtonPressed) return;
  Vector2 screenPosition{static_cast<double>(event.mouseButton.x),
                         static_cast<double>(event.mouseButton.y)};
  // Only top screen receives input
  _screens.back()->HandleClick(screenPosition);
}

void UIManager::PopScreen() { _screens.pop_back(); }

std::unique_ptr<UIScreen> UIManager::CreateScreen(UIScreenType screenType,
                                                  void* data) {
  switch (screenType) {
    case UIScreenType::MainMenu:
      return std::make_unique<MainMenu>(*this);

    case UIScreenType::HUD:
      return std::make_unique<HUD>(*this, static_cast<HUD::Data*>(data));

    case UIScreenType::CompletedMenu:
      return std::make_unique<CompletedMenu>(
          *this, static_cast<CompletedMenu::Data*>(data));

    default:
      return nullptr;
  }
}