#include "Ground.h"

Ground::Ground(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, const Vector2& scale)
    : Entities(name, body, texture, position, scale) {
}
