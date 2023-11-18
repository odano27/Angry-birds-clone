#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include "Entities.h"

class Obstacles : public Entities
{
public:
    Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, const Vector2& scale, int hitPoints, int damage);
    Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, int hitPoints, int damage);
    Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, int hitPoints);
    Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position);

    int GetDamage() override;

private:
    int _hitPoints;
    int _damage;
    
};

#endif // __OBSTACLES_H__