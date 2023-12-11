#include "Score.h"

#define POINTSPERENEMY 100
#define POINTSPERBIRD 150

Score::Score() {

}

int Score::EnemyDestroyed() {
    return POINTSPERENEMY;
}

int Score::BirdUnused(int numOfBirds) {
    return POINTSPERBIRD * numOfBirds;
}