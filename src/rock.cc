#include "rock.h"

#include "player.h"

namespace {
  const int kSpriteCount = 8;
  const int kSize = 16;
}

Rock::Rock(float x, float y) : Object(x, y) {
  int i = rand() % kSpriteCount;
  sprite.reset(new Sprite("sprites", 0 + kSize * (i % 4), 64 + kSize * (i / 4), kSize, kSize));
}

void Rock::draw(Graphics& graphics) {
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2);
}

bool Rock::is_touching(float tx, float ty) {
  float dx = x - tx;
  float dy = y - ty;
  int r = (kSize + Player::kSize) / 3;
  return dx * dx + dy * dy < r * r;
}
