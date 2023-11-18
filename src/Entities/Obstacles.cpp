#include "Obstacles.h"

Obstacles::Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, const Vector2& scale, int hitPoints, int damage)
    : Entities(name, body, texture, position, scale), _hitPoints(hitPoints), _damage(damage) {
}

Obstacles::Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, int hitPoints, int damage)
    : Entities(name, body, texture, position), _hitPoints(hitPoints), _damage(damage) {
}

Obstacles::Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, int hitPoints)
    : Entities(name, body, texture, position), _hitPoints(hitPoints), _damage(15) {
}

Obstacles::Obstacles(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position)
    : Entities(name, body, texture, position), _hitPoints(50), _damage(15) {
}

int Obstacles::GetDamage() {
    return _damage;
}