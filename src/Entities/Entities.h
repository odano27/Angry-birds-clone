#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include <b2_body.h>

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

#include "Renderer.h"
#include "Vector2.h"

class Entities {
  public:
    Entities(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position);
    Entities(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, const Vector2& scale);
    Entities(const std::string& name, b2Body* body, sf::Shape* shape, const Vector2& position);
    virtual ~Entities();

    void Draw(Renderer& renderer, double t);
    void ApplyForce(float x, float y, float n); //don't know if this is needed
    virtual void CollideWith(Entities* other); //called when collision happens
    void Update(Renderer& renderer); //called every frame
    void SetTexture(const std::string& filename); 
    virtual int GetDamage();
    virtual bool IsBird() const { return false; }
    virtual bool isEnemy() const { return false; } // Default false for entities, enemy overrides to yes. 

    b2Body* GetBody() const;
    bool IsDestroyed() const;

  private:
    int hitPoints;
    int damage;
    bool isDestroyed;

    std::string _name;
    b2Body* _body;
    sf::Shape* _shape;
    sf::Sprite _sprite;
    const sf::Texture* _texture;
    Vector2 _position;
    Vector2 _prevPosition;
    Vector2 _scale;
};

#endif  // _ENTITIES_H_
