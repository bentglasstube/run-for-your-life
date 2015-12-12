#include "rock.h"

Rock::Rock(float x, float y) : Object(x, y) {
  sprite.reset(new Sprite("sprites", 64, 0, 16, 16));
}

void Rock::draw(Graphics& graphics) {
  sprite->draw(graphics, x - 8, y - 8);
}
