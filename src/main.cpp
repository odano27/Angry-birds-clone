#include <SFML/Window.hpp>
#include <iostream>

int main() {
  std::cout << "Hello World!" << std::endl;

  sf::Window window(sf::VideoMode(640, 480), "Angry Birds");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
  }
}