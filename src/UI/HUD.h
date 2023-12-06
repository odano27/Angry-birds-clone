#pragma once

#include "UIScreen.h"

class HUD : public UIScreen, public IGameEventHandler {
 public:
  struct Data {
    int levelIndex;
    int enemiesTotal;
  };

  HUD(IUIManager& manager, Data* data);
  ~HUD();

  UIScreenType GetType() override;

  void HandleGameEvent(const GameEvent& event) override;

 private:
  const std::string GetLevelStr(int levelIndex);
  const std::string GetGoalStr(int total, int destroyed = 0);

  void RestartLevel();
  void BackToMenu();
};
