#pragma once

#include <boost/shared_ptr.hpp>
#include <map>
#include <noise/noise.h>

#include "graphics.h"
#include "sprite.h"

class Map {
  public:

    enum Terrain { SNOW, ICE, WATER };

    Map();

    void draw(Graphics& graphics, float dx, float dy);

    Terrain get(float x, float y);

  private:

    noise::module::Perlin perlin;
    std::map<Terrain, boost::shared_ptr<Sprite>> sprites;

};
