#pragma once

#include "Birds.h"
#include "UIScreen.h"

class HUD : public UIScreen, public IGameEventHandler {
 public:
  struct Data {
    int levelIndex;
    int enemiesTotal;
    std::map<BirdType, int> amountByBird;
  };

  HUD(IUIManager& manager, Data* data);
  ~HUD();

  UIScreenType GetType() override;

  void HandleGameEvent(const GameEvent& event) override;

 private:
  void AddBirdButton(const Vector2& position, BirdType type, int amount,
                     bool selected);

  const std::string GetLevelStr(int levelIndex) const;
  const std::string GetGoalStr(int total, int destroyed = 0) const;
  const std::string GetAmountStr(int amount, sf::Color& color) const;
  Vector2 GetBirdScale(BirdType type, bool selected) const;
  Vector2 GetBirdPosition(int index) const;

  void SelectBird(BirdType type);
  void RestartLevel();
  void BackToMenu();
};
