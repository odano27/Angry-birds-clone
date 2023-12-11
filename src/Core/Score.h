#pragma once

#include <utility>

#include "Birds.h"

class Score {
  public:
    Score();
    int EnemyDestroyed();
    int BirdUnused(std::pair<BirdType, int>);

};