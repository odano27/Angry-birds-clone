#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include "AssetLoader.h"
#include "Entities.h"

enum class ObstacleType {
  Plank_ver,
  Plank_hor,
};

class Obstacles : public Entities {
 public:
  Obstacles(ObstacleType type, const Vector2& screenPos, Renderer& renderer,
            Physics& physics, AssetLoader& assets);
};

#endif  // __OBSTACLES_H__