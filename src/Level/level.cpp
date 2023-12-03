#include "level.hpp"

#include "Enemy.h"
#include "Ground.h"
#include "Obstacles.h"

Level::Level(Physics& physics, GameEventBus& eventBus, AssetLoader& assets)
    : _physics(physics), _eventBus(eventBus), _assets(assets) {
  _activeBird = nullptr;
}

Level::~Level() {
  for (auto& entity : _entities) entity->DestroyBody(_physics);
}

void Level::Draw(Renderer& renderer, double t) {
  for (auto& entity : _entities) {
    entity->Draw(renderer, t);

    if (entity->IsDestroyed()) entity->DestroyBody(_physics);
  }
}

bool Level::isCompleted() const {
  // check if level still has enemies alive or not -> completed if not
  for (const auto& entity : _entities) {
    // check if current entity is enemy
    if (entity->isEnemy() && !entity->IsDestroyed()) {
      // if any alive enemy exists, level not completed
      return false;
    }
  }
  // if no alive enemies, level completed
  return true;
}

void Level::CerateLevel(int levelIndex, Renderer& renderer) {
  _levelIndex = levelIndex;
  if (levelIndex == 0)
    CreateLevel1(renderer);
  else if (levelIndex == 1)
    CreateLevel2(renderer);
  else if (levelIndex == 2)
    CreateLevel3(renderer);
}

void Level::RestartLevel(Renderer& renderer) {
  for (auto& entity : _entities) entity->DestroyBody(_physics);
  _entities.clear();
  CerateLevel(_levelIndex, renderer);
}

// Level with 2 red birds, one enemy on a plank (picture in plan folder)
void Level::CreateLevel1(Renderer& renderer) {
  AddEntity(new Ground(renderer, _physics, _assets));

  AddEntity(
      new Birds(BirdType::Red, {430.0, 50.0}, renderer, _physics, _assets));
  AddEntity(
      new Birds(BirdType::Red, {400.0, 200.0}, renderer, _physics, _assets));

  AddEntity(
      new Enemy(EnemyType::Pig, {590.0, 230.0}, renderer, _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {600.0, 290.0}, renderer,
                          _physics, _assets));
}

// Level with 2 red and 2 yellow birds, 2 enemies, one inside plank house
// (picture in plan folder)
void Level::CreateLevel2(Renderer& renderer) {
  AddEntity(new Ground(renderer, _physics, _assets));

  AddEntity(
      new Birds(BirdType::Red, {230.0, 50.0}, renderer, _physics, _assets));
  AddEntity(
      new Birds(BirdType::Red, {200.0, 200.0}, renderer, _physics, _assets));

  AddEntity(
      new Birds(BirdType::Yellow, {330.0, 50.0}, renderer, _physics, _assets));
  AddEntity(
      new Birds(BirdType::Yellow, {300.0, 200.0}, renderer, _physics, _assets));

  AddEntity(
      new Enemy(EnemyType::Pig, {500.0, 340.0}, renderer, _physics, _assets));
  AddEntity(
      new Enemy(EnemyType::Pig, {640.0, 340.0}, renderer, _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {600.0, 290.0}, renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_ver, {700.0, 290.0}, renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_hor, {610.0, 255.0}, renderer,
                          _physics, _assets));
}

// Level with 2red, 2 yellow and 1 big red birds, 2 enemies, both inside plank
// houses (picture in plan folder)
void Level::CreateLevel3(Renderer& renderer) {
  AddEntity(new Ground(renderer, _physics, _assets));

  AddEntity(
      new Birds(BirdType::Red, {230.0, 50.0}, renderer, _physics, _assets));
  AddEntity(
      new Birds(BirdType::Red, {200.0, 200.0}, renderer, _physics, _assets));

  AddEntity(
      new Birds(BirdType::Yellow, {330.0, 50.0}, renderer, _physics, _assets));
  AddEntity(
      new Birds(BirdType::Yellow, {300.0, 200.0}, renderer, _physics, _assets));

  AddEntity(
      new Birds(BirdType::Big_Red, {550.0, 50.0}, renderer, _physics, _assets));

  AddEntity(
      new Enemy(EnemyType::Pig, {440.0, 340.0}, renderer, _physics, _assets));
  AddEntity(
      new Enemy(EnemyType::Pig, {640.0, 340.0}, renderer, _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {400.0, 290.0}, renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_ver, {500.0, 290.0}, renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_hor, {410.0, 255.0}, renderer,
                          _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {600.0, 290.0}, renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_ver, {700.0, 290.0}, renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_hor, {610.0, 255.0}, renderer,
                          _physics, _assets));
}

void Level::AddEntity(Entities*&& entity) {
  _entities.push_back(std::unique_ptr<Entities>(std::move(entity)));
}