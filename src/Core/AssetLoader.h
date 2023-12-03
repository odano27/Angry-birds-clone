#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class AssetLoader {
 public:
  const sf::Font& GetFont(const std::string& name);
  const sf::Texture& GetTexture(const std::string& name, bool repeated = false);

 private:
  std::unique_ptr<sf::Font> LoadFont(const std::string& name);
  std::unique_ptr<sf::Texture> LoadTexture(const std::string& name,
                                           bool repeated = false);

  std::unordered_map<std::string, std::unique_ptr<sf::Font>> _fontByName;
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> _textureByName;
};
