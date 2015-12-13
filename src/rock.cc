#include "rock.h"

namespace {
  const int kSpriteCount = 8;
}

Rock::Rock(float x, float y) : Object(x, y) {
  int i = rand() % kSpriteCount;
  sprite.reset(new Sprite("sprites", 0 + kSize * (i % 4), 64 + kSize * (i / 4), kSize, kSize));
}

void Rock::draw(Graphics& graphics) {
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2);
}
