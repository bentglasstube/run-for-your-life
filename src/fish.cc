#include "fish.h"

Fish::Fish(float x, float y) : Object(x, y) {
  sprite.reset(new Sprite("sprites", 80, 0, 16, 16));
}

void Fish::draw(Graphics& graphics) {
  sprite->draw(graphics, x - 8, y - 8);
}
