#ifndef __GROUND_H__
#define __GROUND_H__

#include "Entities.h"

class Ground : public Entities
{
public:
    Ground(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, const Vector2& scale);

private:

};

#endif // __GROUND_H__