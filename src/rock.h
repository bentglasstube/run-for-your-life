#pragma once

#include <memory>

#include "object.h"
#include "sprite.h"

class Rock : public Object {
  public:

    Rock(float x, float y);

    void draw(Graphics& graphics, const Map::Terrain t);
    void collide(Player& player, Audio& audio);

  private:
    std::unique_ptr<Sprite> sprite;
};
