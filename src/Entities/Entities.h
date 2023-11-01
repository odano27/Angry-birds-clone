#ifndef _ENTITIES_H_
#define _ENTITIES_H_

//#include "box2d hpp file"
//#include "SFML hpp file"
#include <cstdlib>

class Entities
{
public:
    Entities();
    ~Entities();


private:
    float mass;
    float velocity;
    float accelerationX, accelerationY;
    float positionX, positionY;
};

#endif // _ENTITIES_H_
