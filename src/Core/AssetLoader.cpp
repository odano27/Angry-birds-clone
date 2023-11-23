#include "AssetLoader.h"

#include <sstream>

const sf::Font& AssetLoader::GetFont(const std::string& name) {
  if (auto it = _fontByName.find(name); it != _fontByName.end()) {
    return *(it->second);
  }

  std::unique_ptr<sf::Font> font = LoadFont(name);
  _fontByName.insert(std::make_pair(name, std::move(font)));

  return *(_fontByName.find(name)->second);
}

std::unique_ptr<sf::Font> AssetLoader::LoadFont(const std::string& name) {
  std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
  std::stringstream path;
  path << "src/Assets/Fonts/" << name << ".ttf" << std::flush;
  font->loadFromFile(path.str());
  return font;
}