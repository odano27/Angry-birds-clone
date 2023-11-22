#pragma once

#include "Input.h"
#include "UIScreen.h"

class UIManager : public IInputEventHandler {
 public:
  UIManager();

  void Draw(Renderer& renderer);

  void HandleInputEvent(const sf::Event& event) override;

 private:
  std::unique_ptr<UIScreen> _currentScreen;
};
