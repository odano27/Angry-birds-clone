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
      _score(),
      _assets(assets) {
  _slingshotIndex = -1;
  _previewIndex = -1;
  _lastBirdIndex = -1;
  _enemiesTotal = _enemiesDestroyed = 0;
  _levelCompleted = false;
  _levelScore = 0;

  _eventBus.AddEventHandler(GameEvent::BirdSelected, this);
}

Level::~Level() {
  for (auto& entity : _entities) entity->DestroyBody(_physics);

  _eventBus.RemoveEventHandler(GameEvent::BirdSelected, this);
}

void Level::Draw(Renderer& renderer, double t) {
  bool allBirdsDestroyed = true;
  for (auto it = _entities.begin(); it != _entities.end();) {
    Entities* entity = it->get();
    entity->Draw(renderer, t);

    if (entity->IsDestroyed()) {
      entity->DestroyBody(_physics);

      if (entity->isEnemy()) {
        _levelScore += _score.EnemyDestroyed();
        _enemiesDestroyed++;
        it = _entities.erase(it);

        UpdateHUD();
        continue;
      }
    } else if (entity->IsBird()) {
      allBirdsDestroyed = false;
    }

    it++;
  }

  bool noBirdsLeft = true;
  for (auto pair : _amountByBird) {
    if (pair.second > 0) {
      noBirdsLeft = false;
      break;
    } 
  }

  bool isWin = _enemiesDestroyed >= _enemiesTotal;
  bool isFail = allBirdsDestroyed && noBirdsLeft;

  if (!_levelCompleted && (isWin || isFail)) {
    _levelCompleted = true;

    for (auto& pair : _amountByBird) {
      _levelScore += _score.BirdUnused(pair.second);
    }

    GameEvent e;
    e.type = GameEvent::LevelCompleted;
    e.levelCompleted.lastLevel = _levelIndex == AssetLoader::LEVELS_COUNT - 1;
    e.levelCompleted.levelFailed = !isWin;
    _eventBus.Publish(e);
  }
}

void Level::HandleInputEvent(const sf::Event& event) {
  if (_levelCompleted || _slingshotIndex < 0) return;

  Slingshot& slingshot = static_cast<Slingshot&>(GetEntity(_slingshotIndex));
  sf::Vector2f origin = slingshot.GetSpawnPosition();

  bool canThrow = _amountByBird.at(_selected) > 0;

  if (event.type == sf::Event::MouseButtonPressed) {
    _physics.SetCollisionsEnabled(true);

    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    if (canThrow && slingshot.IsPressed(mouseX, mouseY)) {
      _previewIndex =
          AddEntity(new BirdPreview(_selected, mouseX, mouseY, _assets));
      return;
    }

    // If we click anywhere except slingshot - try to use ability on last bird
    if (_lastBirdIndex < 0 ||
        _lastBirdIndex >= static_cast<int>(_entities.size()))
      return;

    Birds& bird = static_cast<Birds&>(GetEntity(_lastBirdIndex));
    if (bird.CanUseAbility()) {
      bird.UseAbility(_renderer.ScreenToWorld(
          {static_cast<double>(mouseX), static_cast<double>(mouseY)}));
    }
    return;
  }

  if (!canThrow) return;

  if (event.type == sf::Event::MouseButtonReleased) {
    if (_previewIndex < 0) return;

    RemoveEntity(_previewIndex);
    _previewIndex = -1;

    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    int angle = GetAngle(mouseX, mouseY, origin);
    sf::Vector2f dir = origin - sf::Vector2f(mouseX, mouseY);
    float len = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
    float maxStretch = 150.0f;
    if (len > maxStretch) {
      dir /= len;
      len = maxStretch;
      dir *= len;
    }

    sf::Vector2f limitedPosition = origin - dir;

    _lastBirdIndex = AddEntity(
        new Birds(_selected, limitedPosition.x, limitedPosition.y, angle,
                  limitedPosition.x > origin.x, _renderer, _physics, _assets));

    Birds& bird = static_cast<Birds&>(GetEntity(_lastBirdIndex));
    bird.Throw(dir.x, -dir.y, (len / Renderer::PPU) * SPEED_MULT);

    _amountByBird.at(_selected) -= 1;
    UpdateHUD();
    return;
  }

  if (event.type == sf::Event::MouseMoved) {
    if (_previewIndex < 0 ||
        _previewIndex >= static_cast<int>(_entities.size()))
      return;

    sf::Vector2f origin = slingshot.GetSpawnPosition();
    int mouseX = event.mouseMove.x;
    int mouseY = event.mouseMove.y;
    sf::Vector2f stretchVector = sf::Vector2f(mouseX, mouseY) - origin;

    float maxStretchDistance = 150.5f;
    float currentStretchDistance = sqrt(stretchVector.x * stretchVector.x +
                                        stretchVector.y * stretchVector.y);

    if (currentStretchDistance > maxStretchDistance) {
      stretchVector /= currentStretchDistance;
      stretchVector *= maxStretchDistance;
      mouseX = origin.x + stretchVector.x;
      mouseY = origin.y + stretchVector.y;
    }

    int angle = GetAngle(mouseX, mouseY, origin);

    BirdPreview& preview = static_cast<BirdPreview&>(GetEntity(_previewIndex));
    preview.SetPosition(mouseX, mouseY);
    preview.SetRotation(angle);
    preview.SetFlipped(mouseX > origin.x);
  }
}

void Level::HandleGameEvent(const GameEvent& event) {
  if (event.type == GameEvent::BirdSelected) {
    _selected = event.birdSelected.type;
    UpdateHUD();
  }
}

void Level::CreateLevel(int levelIndex) {
  // Prevents unnecessary collisions between level entities
  _physics.SetCollisionsEnabled(false);

  _levelIndex = levelIndex;
  _levelCompleted = false;
  _enemiesTotal = _enemiesDestroyed = 0;
  _lastBirdIndex = -1;
  _amountByBird.clear();

  LevelData levelData;
  if (_assets.TryGetLevelData(levelIndex, levelData)) {
    _amountByBird = levelData.GetAmountByBird();

    // Common entities
    AddEntity(new SpriteEntity({0.0, 0.0}, "bg2", 1, _assets));

    _slingshotIndex = AddEntity(new Slingshot({100.0, 210.0}, _assets));
    AddEntity(new Ground(_renderer, _physics, _assets));

    // Level entities
    for (const LevelData::EnemyData& enemyData : levelData.GetEnemies()) {
      AddEntity(new Enemy(enemyData.type, enemyData.position, _renderer,
                          _physics, _assets));
    }

    for (const LevelData::ObstacleData& obstacleData :
         levelData.GetObstacles()) {
      AddEntity(new Obstacles(obstacleData.type, obstacleData.position,
                              _renderer, _physics, _assets));
    }
  }

  _selected = _amountByBird.begin()->first;

  UpdateHUD();
}

void Level::RestartLevel() {
  ClearLevel();
  CreateLevel(_levelIndex);
}

void Level::NextLevel() {
  ClearLevel();
  CreateLevel(_levelIndex + 1);
}

int Level::GetEnemiesTotal() const { return _enemiesTotal; }

const std::map<BirdType, int>& Level::GetAmountByBird() const {
  return _amountByBird;
}

void Level::ClearLevel() {
  for (auto& entity : _entities) entity->DestroyBody(_physics);
  _entities.clear();
}

void Level::UpdateHUD() const {
  GameEvent e;
  e.type = GameEvent::LevelUpdated;
  e.levelUpdated.index = _levelIndex;
  e.levelUpdated.enemiesTotal = _enemiesTotal;
  e.levelUpdated.enemiesDestroyed = _enemiesDestroyed;
  e.levelUpdated.amountByBird = &_amountByBird;
  e.levelUpdated.selected = _selected;
  _eventBus.Publish(e);
}

int Level::GetAngle(int mouseX, int mouseY, sf::Vector2f origin) const {
  int angle = std::atan2(mouseY - origin.y, mouseX - origin.x) * (180 / b2_pi);
  if (angle < -90)
    angle += 180;
  else if (angle > 90)
    angle -= 180;
  return angle;
}

int Level::AddEntity(Entities*&& entity) {
  if (entity->isEnemy()) _enemiesTotal++;

  int index = _entities.size();
  _entities.push_back(std::unique_ptr<Entities>(std::move(entity)));
  return index;
}

void Level::RemoveEntity(int index) {
  _entities.erase(_entities.begin() + index);
}

Entities& Level::GetEntity(int index) const { return *_entities.at(index); }

void Level::Update(double deltaTime) {
  for (auto& entity : _entities) {
    if (entity->IsBird()) {
      Birds* bird = dynamic_cast<Birds*>(entity.get());
      bird->Update(deltaTime);
    }
  }
}

int Level::GetLevelScore() const {
  return _levelScore;
}