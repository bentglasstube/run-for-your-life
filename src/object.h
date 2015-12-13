#pragma once

#include "audio.h"
#include "graphics.h"
#include "map.h"

class Object {
  public:

    Object(float x, float y);

    virtual bool update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float vx, const float vy);
    virtual void draw(Graphics& graphics, const Map::Terrain t) = 0;

    virtual bool is_touching(const float tx, const float ty);

    float get_x() { return x; }
    float get_y() { return y; }

  protected:

    static const int kSize = 16;

    float x, y;
};
