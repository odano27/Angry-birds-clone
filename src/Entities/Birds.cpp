#include "Birds.h"

Birds::Birds(BirdType type, const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position)
    : Entities(name, body, texture, position), _type(type) {
    switch (_type) {
        case BirdType::Red:
            hitPoints = 100;
            damage = 10;
            break;
        case BirdType::Yellow:
            hitPoints = 100;
            damage = 10;
            break;
        case BirdType::Big_Red:
            hitPoints = 200;
            damage = 30;
            break;
    }
}


void Birds::ability(Vector2 mouseLocation) {
    switch (_type) {
        case BirdType::Red: //nothing
            break;
        case BirdType::Big_Red: //nothing
            break;
        case BirdType::Yellow:
            float origSpeed = this->GetBody()->GetLinearVelocity().Length();
            b2Vec2 direction(mouseLocation.x - this->GetBody()->GetPosition().x, mouseLocation.y - this->GetBody()->GetPosition().y);
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            b2Vec2 normalizedDirection = b2Vec2(direction.x / length, direction.y / length);
            float speed = origSpeed * 3; //replace with desired speed
            b2Vec2 velocity = speed * normalizedDirection;
            this->GetBody()->SetLinearVelocity(velocity);
            break;
    }
}

int Birds::GetDamage() {
    return damage*this->GetBody()->GetLinearVelocity().Length();
}