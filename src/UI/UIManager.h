#pragma once

#include "AssetLoader.h"
#include "Input.h"
#include "UIScreen.h"

class UIManager : public IInputEventHandler {
 public:
  UIManager(AssetLoader& assets);

  void Draw(Renderer& renderer);

  void HandleInputEvent(const sf::Event& event) override;

 private:
  AssetLoader& _assets;
  std::unique_ptr<UIScreen> _currentScreen;
};
