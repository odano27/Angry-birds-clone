#include "level.hpp"

#include <cmath>

#include "BirdPreview.h"
#include "Enemy.h"
#include "Ground.h"
#include "Obstacles.h"
#include "Slingshot.h"

Level::Level(Renderer& renderer, Physics& physics, GameEventBus& eventBus,
             AssetLoader& assets)
    : _renderer(renderer),
      _physics(physics),
      _eventBus(eventBus),
      _assets(assets) {
  _slingshotIndex = -1;
  _previewIndex = -1;
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

void Level::HandleInputEvent(const sf::Event& event) {
  if (_slingshotIndex < 0) return;

  Slingshot& slingshot = static_cast<Slingshot&>(GetEntity(_slingshotIndex));
  sf::Vector2f origin = slingshot.GetSpawnPosition();

  if (event.type == sf::Event::MouseButtonPressed) {
    _physics.SetCollisionsEnabled(true);

    if (slingshot.IsPressed(event.mouseButton.x, event.mouseButton.y)) {
      _previewIndex = AddEntity(new BirdPreview(
          BirdType::Red, event.mouseButton.x, event.mouseButton.y, _assets));
    }
  } else if (event.type == sf::Event::MouseButtonReleased) {
    if (_previewIndex < 0) return;

    RemoveEntity(_previewIndex);
    _previewIndex = -1;

    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    int angle = GetAngle(mouseX, mouseY, origin);
    sf::Vector2f dir = origin - sf::Vector2f(mouseX, mouseY);
    float len = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));

    int birdIndex =
        AddEntity(new Birds(BirdType::Red, mouseX, mouseY, angle,
                            mouseX > origin.x, _renderer, _physics, _assets));

    Birds& bird = static_cast<Birds&>(GetEntity(birdIndex));
    bird.Throw(dir.x, -dir.y, (len / Renderer::PPU) * SPEED_MULT);
  } else if (event.type == sf::Event::MouseMoved) {
    if (_previewIndex < 0) return;

    int mouseX = event.mouseMove.x;
    int mouseY = event.mouseMove.y;
    int angle = GetAngle(mouseX, mouseY, origin);

    BirdPreview& preview = static_cast<BirdPreview&>(GetEntity(_previewIndex));
    preview.SetPosition(mouseX, mouseY);
    preview.SetRotation(angle);
    preview.SetFlipped(mouseX > origin.x);
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

void Level::CerateLevel(int levelIndex) {
  // Prevents unnecessary collisions between level entities
  _physics.SetCollisionsEnabled(false);

  _levelIndex = levelIndex;

  CreateCommon();
  if (levelIndex == 0)
    CreateLevel1();
  else if (levelIndex == 1)
    CreateLevel2();
  else if (levelIndex == 2)
    CreateLevel3();
}

void Level::RestartLevel() {
  for (auto& entity : _entities) entity->DestroyBody(_physics);
  _entities.clear();
  CerateLevel(_levelIndex);
}

void Level::CreateCommon() {
  _slingshotIndex = AddEntity(new Slingshot({100.0, 210.0}, _assets));
  AddEntity(new Ground(_renderer, _physics, _assets));
}

// Level with 2 red birds, one enemy on a plank (picture in plan folder)
void Level::CreateLevel1() {
  AddEntity(
      new Enemy(EnemyType::Pig, {590.0, 230.0}, _renderer, _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {600.0, 290.0}, _renderer,
                          _physics, _assets));
}

// Level with 2 red and 2 yellow birds, 2 enemies, one inside plank house
// (picture in plan folder)
void Level::CreateLevel2() {
  AddEntity(
      new Enemy(EnemyType::Pig, {500.0, 340.0}, _renderer, _physics, _assets));
  AddEntity(
      new Enemy(EnemyType::Pig, {640.0, 340.0}, _renderer, _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {600.0, 290.0}, _renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_ver, {700.0, 290.0}, _renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_hor, {610.0, 255.0}, _renderer,
                          _physics, _assets));
}

// Level with 2red, 2 yellow and 1 big red birds, 2 enemies, both inside plank
// houses (picture in plan folder)
void Level::CreateLevel3() {
  AddEntity(
      new Enemy(EnemyType::Pig, {440.0, 340.0}, _renderer, _physics, _assets));
  AddEntity(
      new Enemy(EnemyType::Pig, {640.0, 340.0}, _renderer, _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {400.0, 290.0}, _renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_ver, {500.0, 290.0}, _renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_hor, {410.0, 255.0}, _renderer,
                          _physics, _assets));

  AddEntity(new Obstacles(ObstacleType::Plank_ver, {600.0, 290.0}, _renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_ver, {700.0, 290.0}, _renderer,
                          _physics, _assets));
  AddEntity(new Obstacles(ObstacleType::Plank_hor, {610.0, 255.0}, _renderer,
                          _physics, _assets));
}

int Level::GetAngle(int mouseX, int mouseY, sf::Vector2f origin) {
  int angle = std::atan2(mouseY - origin.y, mouseX - origin.x) * (180 / b2_pi);
  if (angle < -90)
    angle += 180;
  else if (angle > 90)
    angle -= 180;
  return angle;
}

int Level::AddEntity(Entities*&& entity) {
  int index = _entities.size();
  _entities.push_back(std::unique_ptr<Entities>(std::move(entity)));
  return index;
}

void Level::RemoveEntity(int index) {
  _entities.erase(_entities.begin() + index);
}

Entities& Level::GetEntity(int index) { return *_entities.at(index); }
