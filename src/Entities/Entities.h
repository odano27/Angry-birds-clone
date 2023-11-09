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
  Entities(const std::string& name, b2Body* body, sf::Shape* shape,
           const Vector2& position);
  ~Entities();

  void Draw(Renderer& renderer, double t);

  b2Body* GetBody() const;

 private:
  float mass;
  float velocity;
  float accelerationX, accelerationY;

  std::string _name;

  b2Body* _body;
  sf::Shape* _shape;
  Vector2 _position;
  Vector2 _prevPosition;
};

#endif  // _ENTITIES_H_
