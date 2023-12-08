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
  tintColor.a = 200;
  Vector2 windowSize = GetWindowSize();
  _root->AddChild(UIImageBuilder({0.0, 0.0})
                      .WithRect(windowSize.x, windowSize.y)
                      .WithColor(tintColor)
                      .Build());

  // Background
  double hWidth = windowSize.x / 2.0;

  bool isGameWin = _data.lastLevel && !_data.levelFailed;
  sf::Color textColor = _data.levelFailed ? UIText::RED : UIText::GREEN;
  // Title
  _root->AddChild(UITextBuilder(Vector2{hWidth, 150.0},
                                isGameWin ? "Game" : "Level", font, 80)
                      .WithColor(textColor)
                      .WithOutline()
                      .WithOriginAtCenter()
                      .Build());
  _root->AddChild(UITextBuilder(Vector2{hWidth, 240.0},
                                _data.levelFailed ? "Failed" : "Completed",
                                font, 80)
                      .WithColor(textColor)
                      .WithOutline()
                      .WithOriginAtCenter()
                      .Build());

  // Buttons
  Vector2 buttonsPosition = Vector2{hWidth, 355.0};
  _root->AddChild(
      UIButtonBuilder(
          isGameWin ? buttonsPosition
                    : Vector2{buttonsPosition.x - 50.0, buttonsPosition.y},
          true)
          .WithTexture(GetAssets().GetTexture("Button_menu"), Vector2::one())
          .WithClickHandler([&]() { BackToMenu(); })
          .Build());

  if (!isGameWin) {
    _root->AddChild(
        UIButtonBuilder({buttonsPosition.x + 50.0, buttonsPosition.y}, true)
            .WithTexture(
                GetAssets().GetTexture(_data.levelFailed ? "Button_restart"
                                                         : "Button_next"),
                Vector2::one() * (_data.levelFailed ? 1.0 : 0.65))
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
