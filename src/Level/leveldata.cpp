#include "leveldata.hpp"

#include <fstream>

LevelData::LevelData(int index) : _index(index) {}

void LevelData::Load(const std::string& filename) {
  std::ifstream is(filename);
  if (is.rdstate() & (is.badbit | is.failbit)) return;
  while (!is.eof()) ReadLine(is);
}

bool LevelData::IsValid() const {
  return _amountByBird.size() > 0 && _enemies.size() > 0;
}

const std::map<BirdType, int>& LevelData::GetAmountByBird() const {
  return _amountByBird;
}

const std::vector<LevelData::EnemyData>& LevelData::GetEnemies() const {
  return _enemies;
}

const std::vector<LevelData::ObstacleData>& LevelData::GetObstacles() const {
  return _obstacles;
}

void LevelData::ReadLine(std::istream& stream) {
  std::string line;
  std::getline(stream, line);

  // Split line to tokens separated by space
  size_t pos = 0;
  std::vector<std::string> tokens;
  while ((pos = line.find(" ")) != std::string::npos) {
    std::string token = line.substr(0, pos);
    tokens.push_back(token);
    line.erase(0, pos + 1);
  }
  tokens.push_back(line);

  if (tokens.size() <= 0) return;

  // First token is the type of the entity we need to parse
  std::string entityType = tokens[0];

  // Parse Birds
  if (entityType == "b") {
    if (tokens.size() < 3) return;

    BirdType birdType = static_cast<BirdType>(std::stoi(tokens[1]));
    int amount = std::stoi(tokens[2]);
    _amountByBird.insert(std::make_pair(birdType, amount));
    return;
  }

  // Parse Enemies
  if (entityType == "e") {
    if (tokens.size() < 4) return;

    EnemyType enemyType = static_cast<EnemyType>(std::stoi(tokens[1]));
    double positionX = std::stod(tokens[2]);
    double positionY = std::stod(tokens[3]);
    _enemies.push_back(EnemyData{enemyType, Vector2{positionX, positionY}});
    return;
  }

  // Parse Obstacles
  if (entityType == "o") {
    if (tokens.size() < 4) return;

    ObstacleType obstacleType = static_cast<ObstacleType>(std::stoi(tokens[1]));
    double positionX = std::stod(tokens[2]);
    double positionY = std::stod(tokens[3]);
    _obstacles.push_back(
        ObstacleData{obstacleType, Vector2{positionX, positionY}});
    return;
  }
}
