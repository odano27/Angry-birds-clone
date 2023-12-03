#ifndef __GROUND_H__
#define __GROUND_H__

#include "AssetLoader.h"
#include "Entities.h"

class Ground : public Entities {
 public:
  Ground(Renderer& renderer, Physics& physics, AssetLoader& assets);
};

#endif  // __GROUND_H__