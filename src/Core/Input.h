#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

class Input {
 public:
  Input(sf::RenderWindow& window);

  void ProcessEvents();

  bool IsKeyPressed(const sf::Keyboard::Scancode& key) const;

 private:
  sf::RenderWindow& _window;
};