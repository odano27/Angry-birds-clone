#ifndef Birds_h
#define Birds_h

#include "AssetLoader.h"
#include "Entities.h"
#include "SFML/Audio.hpp"

enum class BirdType {
  Red,
  Yellow,
  Big_Red,
};

class Birds : public Entities {
 public:
  Birds(BirdType type, int mouseX, int mouseY, int angle, bool flip,
        Renderer& renderer, Physics& physics, AssetLoader& assets);

  bool IsBird() const override { return true; }
  void CollideWith(Entities* other) override;

  void Throw(float x, float y, float n);
  void UseAbility(
      Vector2 mouseLocation);  // called when mouse is clicked, get world
                               // position of mouse with renderer.ScreenToWorld
                               // before calling this function

  bool CanUseAbility() const;
  int GetDamage() const override;

  static const std::string GetTextureName(BirdType type);
  static double GetRadius(BirdType type);

  void Update(float deltaTime);
  bool HasStoppedMoving() const;

 private:
  BirdType _type;
  bool _canUseAbility;	
  // sf::SoundBuffer _soundBuffer[2];
	// sf::Sound _Sounds[2];

  float _timer;
};

#endif  // BIRDS_H