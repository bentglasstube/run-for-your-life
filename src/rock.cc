#include "rock.h"

#include "random.h"

namespace {
  const int kSpriteCount = 8;
}

Rock::Rock(float x, float y) : Object(x, y) {
  Random r = Random();
  int i = r.rand(0, kSpriteCount - 1);
  sprite.reset(new Sprite("sprites", 0 + kSize * (i % 4), 64 + kSize * (i / 4), kSize, kSize));
}

void Rock::draw(Graphics& graphics, const Map::Terrain) {
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2);
}
