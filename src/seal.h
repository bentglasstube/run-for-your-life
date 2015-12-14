#pragma once

#include <boost/scoped_ptr.hpp>

#include "object.h"
#include "sprite.h"

class Seal : public Object {
  public:

    Seal(float x, float y);

    void update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float dx, const float dy);
    void draw(Graphics& graphics, const Map::Terrain t);
    void collide(Player& player, Audio& audio);

  private:
    float vx, vy;
    float ax, ay;
    int bark_timer;

    boost::scoped_ptr<Sprite> walking, swimming;

    bool facing_left() { return vx < 0; }
};
