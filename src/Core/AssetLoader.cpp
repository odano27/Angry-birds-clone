#include "AssetLoader.h"

#include <sstream>

void AssetLoader::LoadLevels() {
  for (int i = 0; i < LEVELS_COUNT; i++) {
    std::stringstream path;
    path << "src/Assets/Levels/level" << i + 1 << ".txt";

    LevelData levelData(i);
    levelData.Load(path.str());

    if (levelData.IsValid())
      _levelDataByIndex.insert(std::make_pair(i, levelData));
  }
}

const sf::Font& AssetLoader::GetFont(const std::string& name) {
  if (auto it = _fontByName.find(name); it != _fontByName.end()) {
    return *(it->second);
  }

  std::unique_ptr<sf::Font> font = LoadFont(name);
  _fontByName.insert(std::make_pair(name, std::move(font)));

  return *(_fontByName.find(name)->second);
}

const sf::Texture& AssetLoader::GetTexture(const std::string& name,
                                           bool repeated) {
  if (auto it = _textureByName.find(name); it != _textureByName.end())
    return *(it->second);

  std::unique_ptr<sf::Texture> texture = LoadTexture(name, repeated);
  _textureByName.insert(std::make_pair(name, std::move(texture)));

  return *(_textureByName.find(name)->second);
}

bool AssetLoader::TryGetLevelData(int levelIndex, LevelData& levelData) const {
  if (auto it = _levelDataByIndex.find(levelIndex);
      it != _levelDataByIndex.end()) {
    levelData = it->second;
    return true;
  }
  return false;
}

std::unique_ptr<sf::Font> AssetLoader::LoadFont(const std::string& name) {
  std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
  std::stringstream path;
  path << "src/Assets/Fonts/" << name << ".ttf" << std::flush;
  font->loadFromFile(path.str());
  return font;
}

std::unique_ptr<sf::Texture> AssetLoader::LoadTexture(const std::string& name,
                                                      bool repeated) {
  std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
  std::stringstream path;
  path << "src/Assets/Textures/" << name << ".png" << std::flush;
  texture->loadFromFile(path.str());
  texture->setRepeated(repeated);
  texture->setSmooth(true);
  return texture;
}
