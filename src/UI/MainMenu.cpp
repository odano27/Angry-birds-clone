#include "MainMenu.h"

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
  _root->AddChild(
      UIButtonBuilder({hWidth, 85.0}, true)
          .WithRect(100.0f, 35.0f)
          .WithText("Level 1", font)
          .WithClickHandler([]() { std::cout << "Level 1" << std::endl; })
          .Build());

  _root->AddChild(
      UIButtonBuilder({hWidth, 130.0}, true)
          .WithRect(100.0f, 35.0f)
          .WithText("Level 2", font)
          .WithClickHandler([]() { std::cout << "Level 2" << std::endl; })
          .Build());

  _root->AddChild(
      UIButtonBuilder({hWidth, 175.0}, true)
          .WithRect(100.0f, 35.0f)
          .WithText("Level 3", font)
          .WithClickHandler([]() { std::cout << "Level 3" << std::endl; })
          .Build());
}

UIScreenType MainMenu::GetType() { return UIScreenType::MainMenu; }
