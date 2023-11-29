#include "HUD.h"

#include <sstream>

#include "UIButtonBuilder.h"
#include "UITextBuilder.h"

HUD::HUD(IUIManager& manager) : UIScreen({0.0, 0.0}, manager) {
  // TODO: just for test
  const sf::Font& font = GetAssets().GetFont("Roboto-Black");
  _root->AddChild(UIButtonBuilder({GetWindowSize().x - 100.0, 50.0}, true)
                      .WithRect(100.0f, 35.0f)
                      .WithText("Back", font)
                      .WithClickHandler([&]() {
                        Hide();
                        _manager.Show(UIScreenType::MainMenu);
                      })
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
