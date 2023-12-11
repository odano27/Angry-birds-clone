#include "Score.h"

#define POINTS_PER_ENEMY 100
#define POINTS_FOR_RED_BIRD 80
#define POINTS_FOR_YELLOW_BIRD 140
#define POINTS_FOR_BIG_BIRD 160
#define DEFAULT_POINTS_PER_BIRD 80

Score::Score() { }

int Score::EnemyDestroyed() {
    return POINTS_PER_ENEMY;
}

int Score::BirdUnused(std::pair<BirdType, int> birdPair) {
    int scorePerBird = 0;

    switch (birdPair.first) {
        case BirdType::Red:
            scorePerBird = POINTS_FOR_RED_BIRD;
            break;
        case BirdType::Yellow:
            scorePerBird = POINTS_FOR_YELLOW_BIRD;
            break;
        case BirdType::Big_Red:
            scorePerBird = POINTS_FOR_BIG_BIRD;
            break;
        default:
            scorePerBird = DEFAULT_POINTS_PER_BIRD;
            break;
    }

    return scorePerBird * birdPair.second;
}