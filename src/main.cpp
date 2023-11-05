#include <b2_math.h>
#include <b2_world.h>

#include <SFML/Window.hpp>
#include <iostream>

int main() {
  std::cout << "Hello World!" << std::endl;

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  sf::Window window(sf::VideoMode(640, 480), "Angry Birds");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
  }
}