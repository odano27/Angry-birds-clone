#include "HUD.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UITextBuilder.h"

HUD::HUD(IUIManager& manager) : UIScreen({0.0, 0.0}, manager) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");
  _root->AddChild(UIButtonBuilder({100.0, 50.0}, true)
                      .WithRect(100.0f, 35.0f)
                      .WithText("Menu", font)
                      .WithClickHandler([&]() { BackToMenu(); })
                      .Build());
  _root->AddChild(UIButtonBuilder({GetWindowSize().x - 100.0, 50.0}, true)
                      .WithRect(100.0f, 35.0f)
                      .WithText("Restart", font)
                      .WithClickHandler([&]() { RestartLevel(); })
                      .Build());
}

UIScreenType HUD::GetType() { return UIScreenType::HUD; }

void HUD::SetLevelNumber(int levelNumber) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");

  std::stringstream s;
  s << "Level " << levelNumber;

  _root->AddChild(
      UITextBuilder({GetWindowSize().x / 2.0, 25.0}, s.str(), font, 30)
          .WithColor(sf::Color::Red)
          .WithOriginAtCenter()
          .Build());
}

void HUD::RestartLevel() {
  GameEvent e;
  e.type = GameEvent::RestartLevel;
  GetEventBus().Publish(e);
}

void HUD::BackToMenu() {
  Hide();

  GameEvent e;
  e.type = GameEvent::BackToMenu;
  GetEventBus().Publish(e);
}
