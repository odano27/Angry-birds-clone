#pragma once

#include "UIScreen.h"

class CompletedMenu : public UIScreen {
 public:
  struct Data {
    bool lastLevel;
  };

  CompletedMenu(IUIManager& manager, Data* data);

  UIScreenType GetType() override;

 private:
  bool _lastLevel;

  void StartNextLevel();
};
