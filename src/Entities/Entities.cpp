#include "Entities.h"

#include <b2_math.h>
#include <iostream>
Entities::Entities(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position)
    : _name(name), _body(body), _texture(texture), _position(position), _prevPosition(position) {
      _sprite.setTexture(*texture);
      _shape = nullptr;
      hitPoints = 999999999;
      damage = 0;
}

Entities::Entities(const std::string& name, b2Body* body, const sf::Texture* texture, const Vector2& position, const Vector2& scale)
    : _name(name), _body(body), _texture(texture), _position(position), _prevPosition(position), _scale(scale) {
      _sprite.setTexture(*texture);
      _sprite.setScale(scale.x, scale.y);
      _shape = nullptr;
      hitPoints = 999999999;
      damage = 0;
}

Entities::Entities(const std::string& name, b2Body* body, sf::Shape* shape,
                   const Vector2& position)
    : _name(name), _body(body), _shape(shape) {
  _position = position;
  _prevPosition = position;
  _texture = nullptr;
  hitPoints = 999999999;
  damage = 0;
}

Entities::~Entities() {
  if (_shape != nullptr){
    delete _shape;
  }
}

void Entities::Draw(Renderer& renderer, double t) {
  b2Vec2 bodyPosition = _body->GetPosition();
  Vector2 center = renderer.WorldToScreen({bodyPosition.x, bodyPosition.y});

  // _body.GetAngle(). Note that it's in radians
  if (_texture != nullptr){
  auto size = _sprite.getGlobalBounds().getSize();
  _position = center - Vector2{size.x, size.y} / 2;

  Vector2 framePosition = Vector2::lerp(_prevPosition, _position, t);
  _prevPosition = _position;

  _sprite.setPosition(framePosition.x, framePosition.y);
  renderer.DrawSprite(_sprite);
  }
  if (_shape != nullptr){
  auto size = _shape->getLocalBounds().getSize();
  _position = center - Vector2{size.x, size.y} / 2;

  Vector2 framePosition = Vector2::lerp(_prevPosition, _position, t);
  _prevPosition = _position;

  _shape->setPosition(framePosition.x, framePosition.y);
  renderer.DrawShape(*_shape);
  }
}

void Entities::OnCollision(Entities* other) {
  hitPoints -= other->GetDamage();
  if (hitPoints <= 0) {
    isDestroyed = true;
  }
}

void Entities::ApplyForce(float x, float y, float n) {
    b2Vec2 direction(x, y);
    direction.Normalize();
    b2Vec2 force = n * direction; 
    _body->ApplyForceToCenter(force, true);
}

void Entities::Update(Renderer& renderer) {
  b2Vec2 bodyPosition = _body->GetPosition();
  _position = {bodyPosition.x, bodyPosition.y};

  if (_position.x < 0 || _position.y < 0 || _position.x > renderer.GetWindowSize().x || _position.y > renderer.GetWindowSize().y) {
    isDestroyed = true;
  }

  _sprite.setPosition(_position.x, _position.y);
  _sprite.setRotation(_body->GetAngle() * 180 / b2_pi);   
}

bool Entities::IsDestroyed() const {
  return isDestroyed;
}

b2Body* Entities::GetBody() const { return _body; }
int Entities::GetDamage() {
  return damage;
}