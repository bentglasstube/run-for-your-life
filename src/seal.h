#pragma once

#include <boost/scoped_ptr.hpp>

#include "object.h"
#include "sprite.h"

class Seal : public Object {
  public:

    Seal(float x, float y);

    bool update(const unsigned int elapsed, const Map::Terrain t, const float dx, const float dy);
    void draw(Graphics& graphics, const Map::Terrain t);

    bool facing_left() { return vx < 0; }

  private:
    float vx, vy;
    float ax, ay;

    boost::scoped_ptr<Sprite> walking, swimming;
};
