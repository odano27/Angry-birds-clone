#pragma once

#include "UIScreen.h"

class CompletedMenu : public UIScreen {
 public:
  struct Data {
    bool lastLevel;
    bool levelFailed;
  };

  CompletedMenu(IUIManager& manager, Data* data);

  UIScreenType GetType() override;

 private:
  Data _data;

  void StartLevel();
  void BackToMenu();
};
