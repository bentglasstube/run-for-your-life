#pragma once

#include <boost/scoped_ptr.hpp>

#include "object.h"
#include "sprite.h"

class Fish : public Object {
  public:

    Fish(float x, float y);

    // void update(); // TODO
    void draw(Graphics& graphics);

  private:
    boost::scoped_ptr<Sprite> sprite;
};
