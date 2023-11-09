#include "Input.h"

Input::Input(sf::RenderWindow& window) : _window(window) {}

void Input::ProcessEvents() {
  sf::Event event;
  while (_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) _window.close();
  }
}

bool Input::IsKeyPressed(const sf::Keyboard::Scancode& key) const {
  return sf::Keyboard::isKeyPressed(key);
}
