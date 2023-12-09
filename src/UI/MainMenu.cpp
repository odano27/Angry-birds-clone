#include "MainMenu.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UIImageBuilder.h"
#include "UITextBuilder.h"

MainMenu::MainMenu(IUIManager& manager) : UIScreen({0.0f, 0.0f}, manager) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");

  // Background
  Vector2 windowSize = GetWindowSize();
  _root->AddChild(UIImageBuilder({0.0, 0.0})
                      .WithTexture(GetAssets().GetTexture("bg"))
                      .Build());

  // Title
  _root->AddChild(
      UITextBuilder({windowSize.x / 2.0, 200.0}, "Select Level", font, 80)
          .WithColor(sf::Color::White)
          .WithOutline()
          .WithOriginAtCenter()
          .Build());

  // Buttons
  const int buttonsCount = AssetLoader::LEVELS_COUNT;
  const double buttonW = 100.0;
  double buttonX = (windowSize.x - (buttonW * buttonsCount)) / 2;
  for (int i = 0; i < buttonsCount; i++) {
    AddLevelButton(buttonX + (buttonW * i), 270.0, i);
  }
}

UIScreenType MainMenu::GetType() { return UIScreenType::MainMenu; }

void MainMenu::AddLevelButton(double x, double y, int levelIndex) {
  std::stringstream textureName;
  textureName << "Keyboard & Mouse textures/Light/" << levelIndex + 1
              << "_Key_Light";

  _root->AddChild(
      UIButtonBuilder({x, y})
          .WithTexture(GetAssets().GetTexture(textureName.str()))
          .WithClickHandler([&, levelIndex]() { StartLevel(levelIndex); })
          .Build());
}

void MainMenu::StartLevel(int levelIndex) {
  Hide();

  GameEvent e;
  e.type = GameEvent::StartLevel;
  e.startLevel.index = levelIndex;
  GetEventBus().Publish(e);
}
