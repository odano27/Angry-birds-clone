#include "CompletedMenu.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UIImageBuilder.h"
#include "UITextBuilder.h"

CompletedMenu::CompletedMenu(IUIManager& manager, Data* data)
    : UIScreen({0.0, 0.0}, manager), _data(*data) {
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

  bool isGameWin = _data.lastLevel && !_data.levelFailed;
  // Title
  _root->AddChild(UITextBuilder(position + Vector2{hWidth, 40.0},
                                isGameWin ? "Game" : "Level", font, 30)
                      .WithColor(sf::Color::Yellow)
                      .WithOriginAtCenter()
                      .Build());
  _root->AddChild(UITextBuilder(position + Vector2{hWidth, 80.0},
                                _data.levelFailed ? "Failed" : "Completed",
                                font, 30)
                      .WithColor(sf::Color::Yellow)
                      .WithOriginAtCenter()
                      .Build());

  // Buttons
  Vector2 buttonsPosition = position + Vector2{hWidth, 150.0};
  _root->AddChild(UIButtonBuilder(isGameWin ? buttonsPosition
                                            : Vector2{buttonsPosition.x - 40.0,
                                                      buttonsPosition.y},
                                  true)
                      .WithTexture(GetAssets().GetTexture("Button_menu"),
                                   Vector2::one() * 0.8)
                      .WithClickHandler([&]() { BackToMenu(); })
                      .Build());

  if (!isGameWin) {
    _root->AddChild(
        UIButtonBuilder({buttonsPosition.x + 40.0, buttonsPosition.y}, true)
            .WithTexture(
                GetAssets().GetTexture(_data.levelFailed ? "Button_restart"
                                                         : "Button_next"),
                Vector2::one() * (_data.levelFailed ? 0.8 : 0.5))
            .WithClickHandler([&]() { StartLevel(); })
            .Build());
  }
}

UIScreenType CompletedMenu::GetType() { return UIScreenType::CompletedMenu; }

void CompletedMenu::StartLevel() {
  Hide();

  GameEvent e;
  e.type = _data.levelFailed ? GameEvent::RestartLevel : GameEvent::NextLevel;
  GetEventBus().Publish(e);
}

void CompletedMenu::BackToMenu() {
  Hide();

  GameEvent e;
  e.type = GameEvent::BackToMenu;
  GetEventBus().Publish(e);
}
