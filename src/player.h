#pragma once

#include <boost/scoped_ptr.hpp>

#include "map.h"
#include "sprite.h"

class Player {
  public:

    static const int kSize = 32;

    Player();

    void update(unsigned int elapsed, Map::Terrain terrain);
    void draw(Graphics& graphics, int x, int y);

    void set_vx(float _vx) { vx = _vx; }
    void set_vy(float _vy) { vy = _vy; }
    void set_ax(float _ax) { ax = _ax; }

    float get_vx() { return vx; }
    float get_vy() { return vy; }
    float get_ax() { return ax; }

  private:

    float ax;
    float vx, vy;

    boost::scoped_ptr<Sprite> sprite;
};
