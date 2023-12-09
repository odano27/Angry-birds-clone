#ifndef _LEVELDATA_HPP_
#define _LEVELDATA_HPP_

#include <map>
#include <vector>

#include "Vector2.h"

enum class ObstacleType;
enum class EnemyType;
enum class BirdType;

class LevelData {
 public:
  struct EnemyData {
    EnemyType type;
    Vector2 position;
  };

  struct ObstacleData {
    ObstacleType type;
    Vector2 position;
  };

  LevelData() {}
  LevelData(int index);

  void Load(const std::string& filename);

  bool IsValid() const;

  const std::map<BirdType, int>& GetAmountByBird() const;
  const std::vector<EnemyData>& GetEnemies() const;
  const std::vector<ObstacleData>& GetObstacles() const;

 private:
  int _index;
  std::map<BirdType, int> _amountByBird;
  std::vector<EnemyData> _enemies;
  std::vector<ObstacleData> _obstacles;

  void ReadLine(std::istream& stream);
};

#endif  // _LEVELDATA_HPP_