#pragma once

#include "UIScreen.h"

class MainMenu : public UIScreen {
 public:
  MainMenu(IUIManager& manager);

  UIScreenType GetType() override;

 private:
  void AddLevelButton(double x, double y, int levelIndex, const sf::Font& font);

  void StartLevel(int levelIndex);
};
