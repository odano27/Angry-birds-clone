#include "CompletedMenu.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UIImageBuilder.h"
#include "UITextBuilder.h"

CompletedMenu::CompletedMenu(IUIManager& manager, Data* data)
    : UIScreen({0.0, 0.0}, manager), _lastLevel(data->lastLevel) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");

  // Tint
  sf::Color tintColor = sf::Color::White;
  tintColor.a = 150;
  Vector2 windowSize = GetWindowSize();
  _root->AddChild(UIImageBuilder({0.0, 0.0})
                      .WithRect(windowSize.x, windowSize.y)
                      .WithColor(tintColor)
                      .Build());

  // Background
  float width = 200.0f;
  float height = 200.0f;
  double hWidth = width / 2.0;
  Vector2 position = {300.0, 150.0};
  _root->AddChild(UIImageBuilder(position)
                      .WithRect(width, height)
                      .WithColor(sf::Color::Blue)
                      .Build());

  // Title
  _root->AddChild(UITextBuilder(position + Vector2{hWidth, 40.0},
                                _lastLevel ? "Game" : "Level", font, 30)
                      .WithColor(sf::Color::Yellow)
                      .WithOriginAtCenter()
                      .Build());

  _root->AddChild(
      UITextBuilder(position + Vector2{hWidth, 80.0}, "Completed", font, 30)
          .WithColor(sf::Color::Yellow)
          .WithOriginAtCenter()
          .Build());

  _root->AddChild(UIButtonBuilder(position + Vector2{hWidth, 140.0}, true)
                      .WithRect(100.0f, 35.0f)
                      .WithText(_lastLevel ? "Menu" : "Next Level", font)
                      .WithClickHandler([&]() { StartNextLevel(); })
                      .Build());
}

UIScreenType CompletedMenu::GetType() { return UIScreenType::CompletedMenu; }

void CompletedMenu::StartNextLevel() {
  Hide();

  GameEvent e;
  e.type = _lastLevel ? GameEvent::BackToMenu : GameEvent::NextLevel;
  GetEventBus().Publish(e);
}
