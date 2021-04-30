#include "floating_text.h"

#include <sstream>

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
  std::ostringstream out;
  out << "+" << std::fixed << value;
  text->draw(graphics, out.str(), x, y, Text::CENTER);
}

