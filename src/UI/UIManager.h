#pragma once

#include "Input.h"
#include "UIScreen.h"

class UIManager : public IInputEventHandler, public IUIManager {
 public:
  UIManager(GameEventBus& eventBus, AssetLoader& assets, Vector2 windowSize);

  UIScreen& Show(UIScreenType screenType, void* data = nullptr) override;
  UIScreen* Get(UIScreenType screenType) const;
  void Draw(Renderer& renderer);
  void HideAll();

  void HandleInputEvent(const sf::Event& event) override;

 protected:
  void PopScreen() override;

 private:
  std::vector<std::unique_ptr<UIScreen>> _screens;

  std::unique_ptr<UIScreen> CreateScreen(UIScreenType screenType,
                                         void* data = nullptr);
};
