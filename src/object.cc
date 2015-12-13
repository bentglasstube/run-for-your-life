#include "object.h"

#include "graphics.h"
#include "player.h"

Object::Object(float x, float y) : x(x), y(y) {}

void Object::update(unsigned int elapsed, float vx, float vy) {
  x -= vx * elapsed;
  y -= vy * elapsed;
}

bool Object::is_touching(float tx, float ty) {
  float dx = x - tx;
  float dy = y - ty;
  int r = (kSize + Player::kSize) / 3;
  return dx * dx + dy * dy < r * r;
}
