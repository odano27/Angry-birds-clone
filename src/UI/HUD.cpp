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

  int i = 0;
  for (auto pair : data->amountByBird) {
    AddBirdButton(GetBirdPosition(i), pair.first, pair.second, i == 0);
    i++;
  }

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

  int i = 4, j = 0;
  for (auto pair : *event.levelUpdated.amountByBird) {
    bool selected = pair.first == event.levelUpdated.selected;
    // When updating after switching to next level we might need to add new
    // buttons
    if (i >= _root->GetChildCount()) {
      AddBirdButton(GetBirdPosition(i - (4 + j)), pair.first, pair.second,
                    selected);
    } else {
      UIButton& button = static_cast<UIButton&>(_root->GetChild(i));
      button.SetScale(GetBirdScale(pair.first, selected));

      sf::Color color;
      UIText& amountText = static_cast<UIText&>(_root->GetChild(i + 1));
      amountText.SetText(GetAmountStr(pair.second, color));
      amountText.SetColor(color);
    }
    i += 2;
    j++;
  }
}

void HUD::AddBirdButton(const Vector2& position, BirdType type, int amount,
                        bool selected) {
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");
  const sf::Texture& texture =
      GetAssets().GetTexture(Birds::GetTextureName(type));

  sf::Color color;
  std::string amountStr = GetAmountStr(amount, color);
  Vector2 scale = GetBirdScale(type, selected);

  _root->AddChild(UIButtonBuilder(position, true)
                      .WithTexture(texture, scale)
                      .WithClickHandler([&, type]() { SelectBird(type); })
                      .Build());

  _root->AddChild(
      UITextBuilder({position.x, position.y + 45.0}, amountStr, font, 30)
          .WithColor(color)
          .WithOriginAtCenter()
          .Build());
}

const std::string HUD::GetLevelStr(int levelIndex) const {
  std::stringstream s;
  s << "Level " << levelIndex + 1;
  return s.str();
}

const std::string HUD::GetGoalStr(int total, int destroyed) const {
  std::stringstream s;
  s << "Smashed: " << destroyed << "/" << total;
  return s.str();
}

const std::string HUD::GetAmountStr(int amount, sf::Color& color) const {
  color = amount > 0 ? sf::Color::White : sf::Color::Red;

  std::stringstream s;
  s << "x" << amount;
  return s.str();
}

Vector2 HUD::GetBirdScale(BirdType type, bool selected) const {
  double scale = type == BirdType::Big_Red ? 0.2 : 0.3;
  if (selected) scale += type == BirdType::Big_Red ? 0.05 : 0.1;
  return Vector2::one() * scale;
}

Vector2 HUD::GetBirdPosition(int index) const {
  return {70.0 + (index * 85.0), GetWindowSize().y - 130.0};
}

void HUD::SelectBird(BirdType type) {
  GameEvent e;
  e.type = GameEvent::BirdSelected;
  e.birdSelected.type = type;
  GetEventBus().Publish(e);
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
