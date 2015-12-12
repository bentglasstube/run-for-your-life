#pragma once

#include "graphics.h"

class Object {
  public:

    Object(float x, float y);

    virtual void update(unsigned int elapsed, float vx, float vy);
    virtual void draw(Graphics& graphics) = 0;

    virtual bool is_touching(float tx, float ty);

    float get_x() { return x; }
    float get_y() { return y; }

  protected:

    float x, y;
};
