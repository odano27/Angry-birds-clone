#ifndef ENEMY_H
#define ENEMY_H

#include "Entities.h"

enum class EnemyType {
    Pig,
    Pig_Mustache,
    Pig_King,
};

class Enemy : public Entities 
{
public:
    Enemy(EnemyType type, const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position);
    void CollideWith(Entities* other) override;
    int GetDamage() override;
    bool isEnemy() const override { return true; } // override to be true, default false

   private:
    EnemyType _type;
    int hitPoints;
    int damage;
    int instakillRequirement; //pigs get instakilled when hit with birds with enough damage
};

#endif // ENEMY_H
