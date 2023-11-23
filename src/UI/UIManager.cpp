#include "UIManager.h"

#include "MainMenu.h"

UIManager::UIManager(AssetLoader& assets) : _assets(assets) {
  // TODO: add screen switching
  _currentScreen = std::make_unique<MainMenu>(_assets);
}

void UIManager::Draw(Renderer& renderer) {
  if (_currentScreen != nullptr) _currentScreen->Draw(renderer);
}

void UIManager::HandleInputEvent(const sf::Event& event) {
  if (_currentScreen == nullptr || event.type != sf::Event::MouseButtonPressed)
    return;
  Vector2 screenPosition{static_cast<double>(event.mouseButton.x),
                         static_cast<double>(event.mouseButton.y)};
  _currentScreen->HandleClick(screenPosition);
}
