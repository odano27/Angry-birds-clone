#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include <b2_body.h>

#include <SFML/Graphics.hpp>
#include <string>

#include "Physics.h"
#include "Renderer.h"
#include "Vector2.h"

class Entities {
 public:
  Entities(const std::string& name);
  virtual ~Entities() = default;

  void SetBody(b2Body* body);
  void SetTexture(const sf::Texture& texture, const Vector2& scale);
  void SetTextureRect(const sf::IntRect& rect, bool setOriginToCenter = false);
  void SetRectShape(const Vector2& size);
  void SetCirceShape(int radius);
  void DestroyBody(Physics& physics);

  virtual void Draw(Renderer& renderer, double t);

  virtual void CollideWith(Entities* other);  // called when collision happens
  virtual int GetDamage() const;

  virtual bool IsBird() const { return false; }
  virtual bool isEnemy() const {
    return false;
  }  // Default false for entities, enemy overrides to yes.
  
  bool IsDestroyed() const;
  bool CanCollide() const;
  b2Body* GetBody() const;

 protected:
  int _hitPoints;
  int _damage;

  std::unique_ptr<sf::Sprite> _sprite;

  int _initAngle;

  bool _isDestroyed;
 private:
  std::string _name;

  b2Body* _body;
  std::unique_ptr<sf::Shape> _shape;

  Vector2 _position;
  Vector2 _prevPosition;
};

#endif  // _ENTITIES_H_
