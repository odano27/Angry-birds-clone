#include "MainMenu.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UIImageBuilder.h"
#include "UITextBuilder.h"

MainMenu::MainMenu(IUIManager& manager) : UIScreen({10.0f, 10.0f}, manager) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");

  // Background
  float width = 200.0f;
  float height = 215.0f;
  double hWidth = width / 2.0;
  _root->AddChild(UIImageBuilder({0.0, 0.0})
                      .WithRect(width, height)
                      .WithColor(sf::Color::Blue)
                      .Build());

  // Title
  _root->AddChild(UITextBuilder({hWidth, 25.0}, "Angry Birds", font, 30)
                      .WithColor(sf::Color::Red)
                      .WithOriginAtCenter()
                      .Build());

  // Buttons
  double buttonY = 85.0;
  for (int i = 0; i < 3; i++) {
    AddLevelButton(hWidth, buttonY, i, font);
    buttonY += 45.0;
  }
}

UIScreenType MainMenu::GetType() { return UIScreenType::MainMenu; }

void MainMenu::AddLevelButton(double x, double y, int levelIndex,
                              const sf::Font& font) {
  std::stringstream label;
  label << "Level " << levelIndex + 1;

  _root->AddChild(
      UIButtonBuilder({x, y}, true)
          .WithRect(100.0f, 35.0f)
          .WithText(label.str(), font)
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
