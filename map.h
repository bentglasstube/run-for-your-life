#pragma once

#include <map>
#include <noise/noise.h>

#include "graphics.h"

class Map {
  public:

    enum Terrain { SNOW, ICE, WATER };

    Map();

    void draw(Graphics& graphics);
    void set_offsets(int _xo, int _yo) { xo = _xo; yo = _yo; }

    Terrain get(int x, int y);

  private:

    int xo, yo, seed;
    noise::module::Perlin perlin;
};
