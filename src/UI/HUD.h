#pragma once

#include "UIScreen.h"

class HUD : public UIScreen {
 public:
  HUD(IUIManager& manager);

  UIScreenType GetType() override;

  void SetLevelNumber(int levelNumber);

 private:
  void RestartLevel();
  void BackToMenu();
};
