#include "level.hpp"

//Level::Level() : currentLevel(1) { 
//  CreateLevel1(); 
//}

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

bool Level::isCompleted() const {
  //check if level still has enemies alive or not -> completed if not
  for (const Entities* entity : entities) {
    //check if current entity is enemy
    if (entity->isEnemy() && !entity->IsDestroyed()) {
      //if any alive enemy exists, level not completed
      return false;
    }
  }
  // if no alive enemies, level completed
  return true;
}

const std::vector<Entities*>& Level::GetEntities() const { return entities; }

/*void Level::SwitchToLevel(int levelNumber) {
  // Delete entities of current level to not interfere with next levels entities
  for (Entities* entity : entities) {
    delete entity;
  }
  entities.clear();

  //switch level
  currentLevel = levelNumber;
  
  if (currentLevel == 1) {
    CreateLevel1();
  }
  else if (currentLevel == 2) {
    CreateLevel2();
  }
  else if (currentLevel == 3) {
    CreateLevel3();
  } 
}*/

/*void CreateLevel1(Renderer& renderer, Physics& physics) {  // Level with 2 red birds, one enemy on a plank (picture in plan folder)
  // Add two red birds
  for (int i = 0; i < 2; i++) {
    //Create physics body and position for each bird                                  !!TODO implement physics and pos

    //Create the birds
    //Birds* redBird = new Birds(BirdType::Red, "Red", body, texture, position);      !!TODO ADD physics, texture, position
    AddEntity(redBird);
  }
  
  //Add enemy
  { 
    //Create physics and position                                                    !!TODO Add physics

    //Crete the enemy
    Enemy* enemy = new Enemy(EnemyType::Pig, "Pig", body, texture, position)
  }

  //TODO ADD PLANK

  //TODO ADD GROUND
  
}*/

// Level with 2 red and 2 yellow birds, 2 enemies, one inside plank house (picture in plan folder)
//void CreateLevel2();

// Level with 2red, 2 yellow and 1 big red birds, 2 enemies, both inside plank houses (picture in plan folder)
//void CreateLevel3();