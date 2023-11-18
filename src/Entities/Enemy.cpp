#include "Enemy.h"

Enemy::Enemy(EnemyType type, const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position)
    : Entities(name, body, texture, position), _type(type) {
    switch (_type) {
        case EnemyType::Pig:
            hitPoints = 100;
            damage = 10;
            instakillRequirement = 30;
            break;
        case EnemyType::Pig_Mustache:
            hitPoints = 150;
            damage = 10;
            instakillRequirement = 40;
            break;
        case EnemyType::Pig_King:
            hitPoints = 200;
            damage = 12;
            instakillRequirement = 50;
            break;
    }
}

void Enemy::CollideWith(Entities* other) {
    if (other->IsBird()) {
        if (other->GetDamage() >= instakillRequirement) {
            hitPoints = -1;
        }
        else {
            hitPoints -= other->GetDamage();
        }
    }
}

int Enemy::GetDamage() {
    return damage;
}