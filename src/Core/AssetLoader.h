#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>

#include "leveldata.hpp"

class AssetLoader {
 public:
  static const int LEVELS_COUNT = 3;

  void LoadLevels();

  const sf::Font& GetFont(const std::string& name);
  const sf::Texture& GetTexture(const std::string& name, bool repeated = false);
  bool TryGetLevelData(int levelIndex, LevelData& levelData) const;

 private:
  std::unique_ptr<sf::Font> LoadFont(const std::string& name);
  std::unique_ptr<sf::Texture> LoadTexture(const std::string& name,
                                           bool repeated = false);

  std::unordered_map<std::string, std::unique_ptr<sf::Font>> _fontByName;
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> _textureByName;
  std::unordered_map<int, LevelData> _levelDataByIndex;
};
