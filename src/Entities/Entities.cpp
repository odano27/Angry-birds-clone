#include "Entities.h"

#include <b2_math.h>

Entities::Entities(const std::string& name, b2Body* body, sf::Shape* shape,
                   const Vector2& position)
    : _name(name), _body(body), _shape(shape) {
  _position = position;
  _prevPosition = position;
}

Entities::~Entities() {
  delete _shape;
  // TODO: delete body via event to physics (_world.DestroyBody)
}

void Entities::Draw(Renderer& renderer, double t) {
  b2Vec2 bodyPosition = _body->GetPosition();
  Vector2 center = renderer.WorldToScreen({bodyPosition.x, bodyPosition.y});

  // TODO: use global bounds and apply rotation transformation from
  // _body.GetAngle(). Note that it's in radians
  auto size = _shape->getLocalBounds().getSize();
  _position = center - Vector2{size.x, size.y} / 2;

  Vector2 framePosition = Vector2::lerp(_prevPosition, _position, t);
  _prevPosition = _position;

  _shape->setPosition(framePosition.x, framePosition.y);
  renderer.DrawShape(*_shape);
}

b2Body* Entities::GetBody() const { return _body; }
