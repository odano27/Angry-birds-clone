#include "MainMenu.h"

#include "UIButton.h"
#include "UIImageBuilder.h"
#include "UIText.h"

MainMenu::MainMenu() : UIScreen({10.0f, 10.0f}) {
  // Background
  _root->AddChild(UIImageBuilder({0.0, 0.0})
                      .WithRect(150.0f, 145.0f)
                      .WithColor(sf::Color::Blue)
                      .Build());

  // Buttons
  _root->AddChild(std::make_unique<UIButton>(
      Vector2{25.0, 25.0}, 100.0f, 25.0f, sf::Color::Red,
      []() { std::cout << "Click A" << std::endl; }));

  _root->AddChild(std::make_unique<UIButton>(
      Vector2{25.0, 60.0}, 100.0f, 25.0f, sf::Color::Red,
      []() { std::cout << "Click B" << std::endl; }));

  _root->AddChild(std::make_unique<UIButton>(
      Vector2{25.0, 95.0}, 100.0f, 25.0f, sf::Color::Red,
      []() { std::cout << "Click C" << std::endl; }));
}
