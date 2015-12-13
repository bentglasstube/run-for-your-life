#include "fish.h"

#include "animated_sprite.h"

Fish::Fish(float x, float y) : Object(x, y) {
  sprite.reset(new AnimatedSprite("sprites", 0, 48, kSize, kSize, 4, 8));
  dx = (float) rand() / (float) RAND_MAX * 0.1f - 0.05f;
}

bool Fish::update(const unsigned int elapsed, const Map::Terrain t, const float vx, const float vy) {
  float move = dx;

  switch (t) {
    case Map::SNOW:  break;
    case Map::ICE:   move *= 1.5; break;
    case Map::WATER: return false; // TODO play splash sound
  }

  return Object::update(elapsed, t, vx + move, vy);
}

void Fish::draw(Graphics& graphics, const Map::Terrain) {
  SDL_RendererFlip flip = dx > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2, flip);
}
