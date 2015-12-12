#pragma once

#include <noise/noise.h>

#include "graphics.h"

class Map {
  public:

    enum Terrain { SNOW, ICE, WATER };

    Map();

    void draw(Graphics& graphics, float dx, float dy);

    Terrain get(float x, float y);

  private:

    noise::module::Perlin perlin;

};
