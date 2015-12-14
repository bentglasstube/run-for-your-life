#include "rock.h"

namespace {
  const int kSpriteCount = 8;
}

Rock::Rock(float x, float y) : Object(x, y) {
  int i = rand() % kSpriteCount;
  sprite.reset(new Sprite("sprites", 128 + kSize * (i % 4), 0 + kSize * (i / 4), kSize, kSize));
}

void Rock::draw(Graphics& graphics, const Map::Terrain) {
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2);
}

void Rock::collide(Player& player, Audio& audio) {
  player.trip();
  audio.play_sample("hit");
}
