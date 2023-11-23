#pragma once

#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class AssetLoader {
 public:
  const sf::Font& GetFont(const std::string& name);

 private:
  std::unique_ptr<sf::Font> LoadFont(const std::string& name);

  std::unordered_map<std::string, std::unique_ptr<sf::Font>> _fontByName;
};
