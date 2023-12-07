#ifndef Birds_h
#define Birds_h

#include "AssetLoader.h"
#include "Entities.h"

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

 private:
  BirdType _type;
  bool _canUseAbility;
};

#endif  // BIRDS_H