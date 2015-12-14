#include "floating_text.h"

#include <boost/format.hpp>

namespace {
  const float kFloatVel = 0.005f;
  const int kDuration = 500;
}

FloatingText::FloatingText(float x, float y, int value) : Object(x, y), value(value), life_timer(0) {
  text.reset(new Text("text"));
}

void FloatingText::update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float vx, const float vy) {
  life_timer += elapsed;
  if (life_timer > kDuration) dead = true;

  Object::update(elapsed, audio, t, vx, vy - kFloatVel);
}

void FloatingText::draw(Graphics& graphics, const Map::Terrain) {
  text->draw(graphics, boost::str(boost::format("+%d") % value), x, y, Text::CENTER);
}

