#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Angry Birds");

  Game game(window);
  game.RunLoop();
}