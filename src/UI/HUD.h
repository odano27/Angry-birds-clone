#pragma once

#include "UIScreen.h"

class HUD : public UIScreen {
 public:
  struct Data {
    int levelIndex;
  };

  HUD(IUIManager& manager, Data* data);

  UIScreenType GetType() override;

  void SetLevelIndex(int levelIndex);

 private:
  const std::string GetLevelStr(int levelIndex);

  void RestartLevel();
  void BackToMenu();
};
