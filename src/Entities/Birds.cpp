#include "Birds.h"

#include <b2_circle_shape.h>
#include <b2_fixture.h>

Birds::Birds(BirdType type, int mouseX, int mouseY, int angle, bool flip,
             Renderer& renderer, Physics& physics, AssetLoader& assets)
    : Entities("Bird"), _type(type), _canUseAbility(true) {
  _initAngle = angle;
  _timer = 0.0f;


  switch (type) {
    case BirdType::Red:
      _hitPoints = 50;
      _damage = 10;
      break;

    case BirdType::Yellow:
      _hitPoints = 50;
      _damage = 10;
      break;

    case BirdType::Big_Red:
      _hitPoints = 100;
      _damage = 30;
      break;
  }

  double radius = GetRadius(type);
  Vector2 worldPos = renderer.ScreenToWorld(
      Vector2{static_cast<double>(mouseX), static_cast<double>(mouseY)});

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(worldPos.x, worldPos.y);
  bodyDef.angularDamping = 0.5f;
  bodyDef.linearDamping = 0.5f;

  b2CircleShape shape;
  shape.m_radius = radius / Renderer::PPU;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  b2Body* body = physics.CreateBody(&bodyDef);
  body->CreateFixture(&fixtureDef);

  SetBody(body);

  double d = radius * 2;
  const sf::Texture& texture = assets.GetTexture(GetTextureName(type));
  sf::Vector2u textureSize = texture.getSize();
  SetTexture(texture, {d / textureSize.x * (flip ? -1 : 1), d / textureSize.y});
  _soundBuffer[0].loadFromFile("src/Assets/Sounds/Shoot.wav");
  _soundBuffer[1].loadFromFile("src/Assets/Sounds/Fly.wav");
  _Sounds[0].setBuffer(_soundBuffer[0]);
  _Sounds[1].setBuffer(_soundBuffer[1]);
}

void Birds::CollideWith(Entities* other) {
  // Bird can only use ability when it flies
  _canUseAbility = false;
  Entities::CollideWith(other);
}

void Birds::Throw(float x, float y, float n) {
  b2Vec2 direction(x, y);
  direction.Normalize();
  b2Body* body = GetBody();
  b2Vec2 impulse = body->GetMass() * n * direction;
  body->ApplyLinearImpulseToCenter(impulse, true);
  body->SetAngularVelocity(-n / 25.0f);
  _Sounds[1].play();
}

void Birds::UseAbility(Vector2 mouseLocation) {
  // Bird can only use ability once
  _canUseAbility = false;

  float origSpeed = GetBody()->GetLinearVelocity().Length();
  switch (_type) {
    case BirdType::Red:  // nothing
      break;

    // Big Red's ability is fast acceleration in down direction
    case BirdType::Big_Red:
      GetBody()->SetLinearVelocity(origSpeed * 3 * b2Vec2(0, -1));
      break;

    // Yellow's ability is fast acceleration in click direction
    case BirdType::Yellow:
      b2Vec2 bodyPosition = GetBody()->GetPosition();
      b2Vec2 direction(mouseLocation.x - bodyPosition.x,
                       mouseLocation.y - bodyPosition.y);
      direction.Normalize();
      GetBody()->SetLinearVelocity(origSpeed * 3 * direction);
      break;
  }
}

bool Birds::CanUseAbility() const { return _canUseAbility && !IsDestroyed(); }

int Birds::GetDamage() const {
  float speed = this->GetBody()->GetLinearVelocity().Length();
  return _damage * (speed / 5);
}

const std::string Birds::GetTextureName(BirdType type) {
  switch (type) {
    default:
    case BirdType::Red:
      return "Red";

    case BirdType::Yellow:
      return "Yellow";

    case BirdType::Big_Red:
      return "Big_red";
  }
}

double Birds::GetRadius(BirdType type) {
  switch (type) {
    default:
    case BirdType::Red:
    case BirdType::Yellow:
      return 40.0;

    case BirdType::Big_Red:
      return 50.0;
  }
}

void Birds::Update(float deltaTime) {
  if (this->HasStoppedMoving()) {
    _timer += deltaTime;
    if (_timer >= 1.0f) {
      this->_isDestroyed = true;
    }
  } else {
    _timer = 0.0f;
  }
}

bool Birds::HasStoppedMoving() const {
  const b2Body* body = this->GetBody();

    if (body) {
        float linearThreshold = 0.1f;
        float angularThreshold = 0.2f;
        float angularVelocity = body->GetAngularVelocity();

        float linearVelocity = body->GetLinearVelocity().Length();

        return (linearVelocity < linearThreshold) &&
               (std::abs(angularVelocity) < angularThreshold);
    }
    return false;
}