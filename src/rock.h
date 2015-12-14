#pragma once

#include <boost/scoped_ptr.hpp>

#include "object.h"
#include "sprite.h"

class Rock : public Object {
  public:

    Rock(float x, float y);

    void draw(Graphics& graphics, const Map::Terrain t);
    void collide(Player& player, Audio& audio);

  private:
    boost::scoped_ptr<Sprite> sprite;
};
