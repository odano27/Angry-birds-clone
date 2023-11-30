#include "level.hpp"

// Level::Level() : currentLevel(1) {
//   CreateLevel1();
// }

Level::Level(GameEventBus& eventBus) : _eventBus(eventBus) {}

Level::~Level() {
  for (Entities* entity : entities) {
    GameEvent e;
    e.type = GameEvent::DestroyBody;
    e.destroyBody.body = entity->GetBody();
    _eventBus.Publish(e, true);

    delete entity;
  }
}

void Level::Draw(Renderer& renderer, double t) {
  for (Entities* entity : entities) {
    entity->Draw(renderer, t);
  }
}

void Level::AddEntity(Entities* entity) { entities.push_back(entity); }

bool Level::isCompleted() const {
  // check if level still has enemies alive or not -> completed if not
  for (const Entities* entity : entities) {
    // check if current entity is enemy
    if (entity->isEnemy() && !entity->IsDestroyed()) {
      // if any alive enemy exists, level not completed
      return false;
    }
  }
  // if no alive enemies, level completed
  return true;
}

/*void Level::SwitchToLevel(int levelNumber) {
  // Delete entities of current level to not interfere with next levels entities
  for (Entities* entity : entities) {
    delete entity;
  }
  entities.clear();

  //switch level
  currentLevel = levelNumber;

  if (currentLevel == 1) {
    CreateLevel1();
  }
  else if (currentLevel == 2) {
    CreateLevel2();
  }
  else if (currentLevel == 3) {
    CreateLevel3();
  }
}*/

void Level::CreateLevel1(
    Renderer& renderer,
    Physics& physics) {  // Level with 2 red birds, one enemy on a plank
                         // (picture in plan folder)

  {  // GROUND
    // ground fill the entire bottom of the window
    const Vector2 size = {renderer.GetWindowSize().x,
                          renderer.GetWindowSize().y / 12.0};
    Vector2 screenPos = Vector2{renderer.GetWindowSize().y / 12.0,
                                renderer.GetWindowSize().x / 2.0};
    Vector2 worldPos = renderer.ScreenToWorld(screenPos + (size / 2));
    // creating the ground in b2d
    b2BodyDef bodyDef;
    bodyDef.position.Set(worldPos.x, worldPos.y);
    b2Body* groundBody = physics.CreateBody(&bodyDef);
    b2PolygonShape groundShape;
    groundShape.SetAsBox((size.x / 2.0) / Renderer::PPU,
                         ((size.y / 2.0) / Renderer::PPU));
    groundBody->CreateFixture(&groundShape, 0.0f);

    // create ground view in SFML
    sf::RectangleShape* rectShape = new sf::RectangleShape(
        {static_cast<float>(size.x), static_cast<float>(size.y)});
    rectShape->setFillColor(sf::Color::Blue);
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(
            "src/Assets/Textures/Grass.png")) {  // test sprite
      std::cout << "Error loading texture" << std::endl;
    }
    AddEntity(new Ground("Ground", groundBody, texture.get(), screenPos,
                         Vector2{1.0, 1.0}));
  }
  {  // BIRDS
    const double birdsRadius = 20.0;
    // Add two red birds
    for (int i = 0; i < 2; i++) {
      // Create position for each bird
      Vector2 screenPos =
          Vector2{(renderer.GetWindowSize().x) / 12.0,
                  ((renderer.GetWindowSize().y) / 2.0) +
                      birdsRadius * 2 *
                          i};  // TODO verify that x and y are in right order
      Vector2 worldPos = renderer.ScreenToWorld(screenPos + birdsRadius);

      // Create bird physic body & fixture
      b2BodyDef bodyDef;
      bodyDef.type = b2_dynamicBody;
      bodyDef.position.Set(worldPos.x, worldPos.y);
      b2Body* birdBody = physics.CreateBody(&bodyDef);

      b2CircleShape physShape;
      physShape.m_radius = birdsRadius / Renderer::PPU;
      b2FixtureDef fixtureDef;
      fixtureDef.shape = &physShape;
      fixtureDef.density = 1.0f;
      fixtureDef.friction = 0.3f;
      birdBody->CreateFixture(&fixtureDef);

      // Create bird view
      sf::CircleShape* viewShape = new sf::CircleShape(birdsRadius);
      viewShape->setFillColor(sf::Color::Red);

      // load textures
      auto texture = std::make_unique<sf::Texture>();
      if (!texture->loadFromFile(
              "src/Assets/Textures/Red.png")) {  // test sprite
        std::cout << "Error loading texture" << std::endl;
      }
      AddEntity(
          new Birds(BirdType::Red, "Red", birdBody, texture.get(), screenPos));
    }
  }

  // Add enemy
  {
    const double EnemiesRadius = 15.0;
    // Create position for enemy
    Vector2 screenPos =
        Vector2{renderer.GetWindowSize().x / 1.5,
                renderer.GetWindowSize().y / 10 + EnemiesRadius * 2};
    Vector2 worldPos = renderer.ScreenToWorld(screenPos + EnemiesRadius);

    // Create enemy physic body & fixture
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(worldPos.x, worldPos.y);
    b2Body* enemyBody = physics.CreateBody(&bodyDef);

    b2CircleShape physShape;
    physShape.m_radius = EnemiesRadius / Renderer::PPU;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &physShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    enemyBody->CreateFixture(&fixtureDef);

    // Create bird view
    sf::CircleShape* viewShape = new sf::CircleShape(EnemiesRadius);
    viewShape->setFillColor(sf::Color::Green);

    // load textures
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile("src/Assets/Textures/Pig.png")) {  // test sprite
      std::cout << "Error loading texture" << std::endl;
    }
    AddEntity(
        new Enemy(EnemyType::Pig, "Pig", enemyBody, texture.get(), screenPos));
  }
  // Add plank
  {
    // Create position for plank
    const Vector2 size = {
        renderer.GetWindowSize().x,
        renderer.GetWindowSize().y / 10 - renderer.GetWindowSize().y / 12.0};
    Vector2 screenPos = Vector2{renderer.GetWindowSize().x / 1.5,
                                renderer.GetWindowSize().y / 12.0};
    Vector2 worldPos = renderer.ScreenToWorld(screenPos + size / 2);

    // Create plank physic body & fixture
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(worldPos.x, worldPos.y);
    b2Body* plankBody = physics.CreateBody(&bodyDef);

    b2PolygonShape physShape;
    physShape.SetAsBox((size.x / 2.0) / Renderer::PPU,
                       ((size.y / 2.0) / Renderer::PPU));
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &physShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.7f;
    plankBody->CreateFixture(&fixtureDef);

    // Create plank view
    sf::RectangleShape* viewShape = new sf::RectangleShape(
        {static_cast<float>(size.x), static_cast<float>(size.y)});
    viewShape->setFillColor(sf::Color::White);

    // load textures
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(
            "src/Assets/Textures/Plank.png")) {  // test sprite
      std::cout << "Error loading texture" << std::endl;
    }
    AddEntity(new Obstacles("Plank", plankBody, texture.get(), screenPos));
  }
}

/* // Level with 2 red and 2 yellow birds, 2 enemies, one inside plank house
(picture in plan folder) void Level::CreateLevel2(Renderer& renderer, Physics&
physics) {

  {//GROUND
  //ground fill the entire bottom of the window
  const Vector2 size = {renderer.GetWindowSize().x,
renderer.GetWindowSize().y/12.0}; Vector2 screenPos =
Vector2{renderer.GetWindowSize().y/12.0, renderer.GetWindowSize().x/2.0};
  Vector2 worldPos = renderer.ScreenToWorld(screenPos + (size / 2));
  //creating the ground in b2d
  b2BodyDef bodyDef;
  bodyDef.position.Set(worldPos.x,worldPos.y);
  b2Body* groundBody = physics.CreateBody(&bodyDef);
  b2PolygonShape groundShape;
  groundShape.SetAsBox((size.x/2.0)/Renderer::PPU,
                      ((size.y/2.0)/Renderer::PPU));
  groundBody->CreateFixture(&groundShape, 0.0f);


  //create ground view in SFML
  sf::RectangleShape* rectShape = new sf::RectangleShape(
        {static_cast<float>(size.x), static_cast<float>(size.y)});
  rectShape->setFillColor(sf::Color::Blue);
  auto texture = std::make_unique<sf::Texture>();
  if (!texture->loadFromFile("src/Assets/Textures/Grass.png")) { //test sprite
    std::cout << "Error loading texture" << std::endl;
  }
  AddEntity(new Ground("Ground", groundBody, texture.get(), screenPos,
Vector2{1.0, 1.0}));

  }

  //Birds
  {// Add two red birds
  for (int i = 0; i < 2; i++) {
    //Create physics body and position for each bird !!TODO implement physics
and pos

    //Create the birds !!TODO ADD physics, texture, position AddEntity(new
Birds(BirdType::Red, "Red", birdBody, texture.get(), screenPos));
  }

  // Add two yellow birds
  for (int i = 0; i < 2; i++) {
    //Create physics body and position for each bird !!TODO implement physics
and pos

    //Create the birds !!TODO ADD physics, texture, position AddEntity(new
Birds(BirdType::Yellow, "Yellow", birdBody, texture.get(), screenPos));
  }
  }

  //Enemies
  {
  //Add enemy 1
  {
    //Create physics and position !!TODO Add physics

    //Crete the enemy
    AddEntity(new Enemy(EnemyType::Pig, "Pig1", body, texture, position));
  }

  //Add enemy 2
  {
    //Create physics and position !!TODO Add physics

    //Crete the enemy
    AddEntity(new Enemy(EnemyType::Pig, "Pig2", body, texture, position));
  }
  }

  //Add plank
  {
   //Create position for plank

   // Create plank physic body & fixture

   // Create plank view

   //load textures
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile("src/Assets/Textures/Plank.png")) { //test sprite
      std::cout << "Error loading texture" << std::endl;
    }

    AddEntity(new Obstacles("Plank", plankBody, texture.get(), screenPos));
  }
}
*/

/*
// Level with 2red, 2 yellow and 1 big red birds, 2 enemies, both inside plank
houses (picture in plan folder) void Level::CreateLevel3(Renderer& renderer,
Physics& physics) {

  {//GROUND
  //ground fill the entire bottom of the window
  const Vector2 size = {renderer.GetWindowSize().x,
renderer.GetWindowSize().y/12.0}; Vector2 screenPos =
Vector2{renderer.GetWindowSize().y/12.0, renderer.GetWindowSize().x/2.0};
  Vector2 worldPos = renderer.ScreenToWorld(screenPos + (size / 2));
  //creating the ground in b2d
  b2BodyDef bodyDef;
  bodyDef.position.Set(worldPos.x,worldPos.y);
  b2Body* groundBody = physics.CreateBody(&bodyDef);
  b2PolygonShape groundShape;
  groundShape.SetAsBox((size.x/2.0)/Renderer::PPU,
                      ((size.y/2.0)/Renderer::PPU));
  groundBody->CreateFixture(&groundShape, 0.0f);


  //create ground view in SFML
  sf::RectangleShape* rectShape = new sf::RectangleShape(
        {static_cast<float>(size.x), static_cast<float>(size.y)});
  rectShape->setFillColor(sf::Color::Blue);
  auto texture = std::make_unique<sf::Texture>();
  if (!texture->loadFromFile("src/Assets/Textures/Grass.png")) { //test sprite
    std::cout << "Error loading texture" << std::endl;
  }
  AddEntity(new Ground("Ground", groundBody, texture.get(), screenPos,
Vector2{1.0, 1.0}));

  }

  //Birds
  {// Add two red birds
  for (int i = 0; i < 2; i++) {
    //Create physics body and position for each bird !!TODO implement physics
and pos

    //Create the birds
    //Birds* redBird = new Birds(BirdType::Red, "Red", body, texture, position);
!!TODO ADD physics, texture, position AddEntity(new Birds(BirdType::Red, "Red",
birdBody, texture.get(), screenPos));
  }

  // Add two yellow birds
  for (int i = 0; i < 2; i++) {
    //Create physics body and position for each bird !!TODO implement physics
and pos

    //Create the birds !!TODO ADD physics, texture, position AddEntity(new
Birds(BirdType::Yellow, "Yellow", birdBody, texture.get(), screenPos));
  }
  // Add big red bird
    //Create physics body and position for each bird !!TODO implement physics
and pos

    //Create the birds !!TODO ADD physics, texture, position AddEntity(new
Birds(BirdType::Yellow, "Yellow", birdBody, texture.get(), screenPos));
  }

  //Enemies
  {
  //Add enemy 1
  {
    //Create physics and position !!TODO Add physics

    //Crete the enemy
    AddEntity(new Enemy(EnemyType::Pig, "Pig1", body, texture, position));
  }

  //Add enemy 2
  {
    //Create physics and position !!TODO Add physics

    //Crete the enemy
    AddEntity(new Enemy(EnemyType::Pig, "Pig2", body, texture, position));
  }
  }

  //Add plank 1
  {
   //Create position for plank

   // Create plank physic body & fixture

   // Create plank view

   //load textures
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile("src/Assets/Textures/Plank.png")) { //test sprite
      std::cout << "Error loading texture" << std::endl;
    }

    AddEntity(new Obstacles("Plank", plankBody, texture.get(), screenPos));
  }

  //Add plank 2
  {
   //Create position for plank

   // Create plank physic body & fixture

   // Create plank view

   //load textures
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile("src/Assets/Textures/Plank.png")) { //test sprite
      std::cout << "Error loading texture" << std::endl;
    }

    AddEntity(new Obstacles("Plank", plankBody, texture.get(), screenPos));
  }
}

*/