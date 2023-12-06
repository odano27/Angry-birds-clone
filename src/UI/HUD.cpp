#include "HUD.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UITextBuilder.h"

HUD::HUD(IUIManager& manager, Data* data) : UIScreen({0.0, 0.0}, manager) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");
  _root->AddChild(UIButtonBuilder({GetWindowSize().x - 60.0, 50.0}, true)
                      .WithTexture(GetAssets().GetTexture("Button_menu"),
                                   Vector2::one() * 0.8)
                      .WithClickHandler([&]() { BackToMenu(); })
                      .Build());
  _root->AddChild(UIButtonBuilder({GetWindowSize().x - 140.0, 50.0}, true)
                      .WithTexture(GetAssets().GetTexture("Button_restart"),
                                   Vector2::one() * 0.8)
                      .WithClickHandler([&]() { RestartLevel(); })
                      .Build());

  _root->AddChild(
      UITextBuilder({30.0, 25.0}, GetLevelStr(data->levelIndex), font, 30)
          .WithColor(sf::Color::White)
          .Build());

  _root->AddChild(UITextBuilder({GetWindowSize().x / 2.0, 35.0},
                                GetGoalStr(data->enemiesTotal), font, 30)
                      .WithColor(sf::Color::Green)
                      .WithOriginAtCenter()
                      .Build());

  GetEventBus().AddEventHandler(GameEvent::LevelUpdated, this);
}

HUD::~HUD() { GetEventBus().RemoveEventHandler(GameEvent::LevelUpdated, this); }

UIScreenType HUD::GetType() { return UIScreenType::HUD; }

void HUD::HandleGameEvent(const GameEvent& event) {
  if (event.type != GameEvent::LevelUpdated) return;

  UIText& levelText = static_cast<UIText&>(_root->GetChild(2));
  levelText.SetText(GetLevelStr(event.levelUpdated.index));

  UIText& goalText = static_cast<UIText&>(_root->GetChild(3));
  goalText.SetText(GetGoalStr(event.levelUpdated.enemiesTotal,
                              event.levelUpdated.enemiesDestroyed));
}

const std::string HUD::GetLevelStr(int levelIndex) {
  std::stringstream s;
  s << "Level " << levelIndex + 1;
  return s.str();
}

const std::string HUD::GetGoalStr(int total, int destroyed) {
  std::stringstream s;
  s << "Smashed: " << destroyed << "/" << total;
  return s.str();
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
