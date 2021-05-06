#pragma once

#include <memory>

#include "object.h"
#include "text.h"

class FloatingText : public Object {
  public:

    FloatingText(float x, float y, int value);

    void update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float vx, const float vy);
    void draw(Graphics& graphics, const Map::Terrain t);

  private:

    std::unique_ptr<Text> text;
    int value, life_timer;
};
