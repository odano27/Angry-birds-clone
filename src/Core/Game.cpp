#include "Game.h"

#include <b2_body.h>
#include <b2_circle_shape.h>
#include <b2_fixture.h>
#include <b2_polygon_shape.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "DebugDraw.h"
#include "Entities.h"

Game::Game(sf::RenderWindow& window) : _window(window) {
  _level = nullptr;
  _input = new Input(window);
  _renderer = new Renderer(window);

  DebugDraw* debugDraw = new DebugDraw(*_renderer);
  _physics = new Physics(debugDraw);
}

Game::~Game() {
  // TODO: refactor later, this is just for test
  DeleteLevel();

  delete _level;
  delete _input;
  delete _renderer;
  delete _physics;
}

void Game::RunLoop() {
  double fixedDeltaTime = 1.0 / 50;
  double maxDeltaTime = 1.0 / 3.0;

  // TODO: remove later, this is just for test
  CreateTestLevel();

  sf::Clock clock;
  double accumulated = 0.0;
  while (_window.isOpen()) {
    double elapsed = clock.restart().asSeconds();

    if (elapsed > maxDeltaTime) elapsed = maxDeltaTime;
    accumulated += elapsed;

    // Process Input
    _input->ProcessEvents();

    while (accumulated >= fixedDeltaTime) {
      // Update Physics
      _physics->FixedUpdate(fixedDeltaTime);

      accumulated -= fixedDeltaTime;
    }

    // Rendering
    {
      double t = accumulated / fixedDeltaTime;
      RenderScope scope(*_renderer);

      //  TODO: Draw UI

      // Draw Level
      if (_level != nullptr) _level->Draw(*_renderer, t);

      // Draw physics debug overlay
      if (_input->IsKeyPressed(sf::Keyboard::Scan::D)) _physics->DrawDebug();
    }
  }
}

void Game::CreateTestLevel() {
  _level = new Level();

  // Add floor entity (static)
  {
    const Vector2 size = {600.0, 50.0};
    Vector2 screenPos = Vector2{100.0, 500.0};
    Vector2 worldPos = _renderer->ScreenToWorld(screenPos + (size / 2));

    // Create physics
    b2BodyDef bodyDef;
    bodyDef.position.Set(worldPos.x, worldPos.y);
    b2Body* body = _physics->CreateBody(&bodyDef);

    b2PolygonShape polyShape;
    polyShape.SetAsBox((size.x / 2.0) / Renderer::PPU,
                       ((size.y / 2.0) / Renderer::PPU));
    body->CreateFixture(&polyShape, 0.0f);

    // Create view
    sf::RectangleShape* rectShape = new sf::RectangleShape(
        {static_cast<float>(size.x), static_cast<float>(size.y)});
    rectShape->setFillColor(sf::Color::Blue);

    _level->AddEntity(new Entities("Floor", body, rectShape, screenPos));
  }

  // Add some balls
  {
    const double radius = 50.0;

    for (int i = 0; i < 3; i++) {
      Vector2 screenPos = Vector2{250.0 + radius * i, radius * 2 * i};
      Vector2 worldPos = _renderer->ScreenToWorld(screenPos + radius);

      // Create physics
      b2BodyDef bodyDef;
      bodyDef.type = b2_dynamicBody;
      bodyDef.position.Set(worldPos.x, worldPos.y);
      b2Body* body = _physics->CreateBody(&bodyDef);

      b2CircleShape physShape;
      physShape.m_radius = radius / Renderer::PPU;

      b2FixtureDef fixtureDef;
      fixtureDef.shape = &physShape;
      fixtureDef.density = 1.0f;
      fixtureDef.friction = 0.3f;
      body->CreateFixture(&fixtureDef);

      // Create view
      sf::CircleShape* viewShape = new sf::CircleShape(radius);
      viewShape->setFillColor(sf::Color::Green);

      _level->AddEntity(new Entities("Ball", body, viewShape, screenPos));
    }
  }
}

void Game::DeleteLevel() {
  if (_level == nullptr) return;

  for (const Entities* entity : _level->GetEntities()) {
    _physics->DestroyBody(entity->GetBody());
  }
}
