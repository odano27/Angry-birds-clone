#include "Input.h"

Input::Input(sf::RenderWindow& window) : _window(window) {}

void Input::ProcessEvents() {
  sf::Event event;
  while (_window.pollEvent(event)) {
    auto range = _eventHandlers.equal_range(event.type);
    for (auto it = range.first; it != range.second; ++it)
      it->second->HandleInputEvent(event);

    if (event.type == sf::Event::Closed) _window.close();
  }
}

bool Input::IsKeyPressed(const sf::Keyboard::Scancode& key) const {
  return sf::Keyboard::isKeyPressed(key);
}

void Input::AddEventHandler(sf::Event::EventType eventType,
                            IInputEventHandler* handler) {
  _eventHandlers.insert(std::make_pair(eventType, handler));
}
