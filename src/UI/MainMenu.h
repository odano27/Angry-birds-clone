#pragma once

#include "UIScreen.h"

class MainMenu : public UIScreen {
 public:
  MainMenu(IUIManager& manager);

  UIScreenType GetType() override;
};
