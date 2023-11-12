#ifndef Birds_h
#define Birds_h

#include "Entities.h"

enum class BirdType {
    Red,
    Yellow,
    Big_Red,
};

class Birds : public Entities
{
public:
    Birds(BirdType type, const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position);
    int GetDamage() override;

    void ability(Vector2 mouseLocation); //shouid be called when mouse is clicked

private:
    BirdType _type;
    int hitPoints;
    int damage;
};

#endif // BIRDS_H