#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "leveldata.hpp"
#include "../Entities/Entities.h"
#include "../Entities/Birds.h"
#include <vector>

class Level {
public:
    Level();
    ~Level();
    void loadLevel(LevelData& data);
    bool isCompleted() const;
    int calculateScore();

   private:
    std::vector<Entities*> entities;
    Birds* activeBird;
    int enemyCount;
    int score;
    bool levelComplete;
};

#endif // _LEVEL_HPP_
