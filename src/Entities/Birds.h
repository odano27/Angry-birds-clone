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
  Birds(BirdType type, int mouseX, int mouseY, Renderer& renderer,
        Physics& physics, AssetLoader& assets);

  bool IsBird() const override { return true; }

  void ApplyImpulse(float x, float y, float n);
  void ability(
      Vector2 mouseLocation);  // called when mouse is clicked, get world
                               // position of mouse with renderer.ScreenToWorld
                               // before calling this function

  int GetDamage() const override;

  static const std::string GetTextureName(BirdType type);
  static double GetRadius(BirdType type);

 private:
  BirdType _type;
};

#endif  // BIRDS_H