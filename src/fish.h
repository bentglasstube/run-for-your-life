#pragma once

#include <boost/scoped_ptr.hpp>

#include "object.h"
#include "sprite.h"

class Fish : public Object {
  public:

    Fish(float x, float y);

    bool update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float vx, const float vy);
    void draw(Graphics& graphics, const Map::Terrain t);

  private:
    boost::scoped_ptr<Sprite> sprite;
    float dx;
};
