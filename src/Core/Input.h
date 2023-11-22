#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <unordered_map>

class IInputEventHandler {
 public:
  virtual ~IInputEventHandler() = default;

  virtual void HandleInputEvent(const sf::Event& event) = 0;
};

class Input {
 public:
  Input(sf::RenderWindow& window);

  void ProcessEvents();

  bool IsKeyPressed(const sf::Keyboard::Scancode& key) const;

  void AddEventHandler(sf::Event::EventType eventType,
                       IInputEventHandler* handler);

 private:
  sf::RenderWindow& _window;
  std::unordered_multimap<sf::Event::EventType, IInputEventHandler*>
      _eventHandlers;
};