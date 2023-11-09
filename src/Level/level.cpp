#include "level.hpp"

Level::Level() {}

Level::~Level() {
  for (Entities* entity : entities) {
    delete entity;
  }
}

void Level::Draw(Renderer& renderer, double t) {
  for (Entities* entity : entities) {
    entity->Draw(renderer, t);
  }
}

void Level::AddEntity(Entities* entity) { entities.push_back(entity); }

const std::vector<Entities*>& Level::GetEntities() const { return entities; }
