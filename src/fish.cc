#include "fish.h"

#include "animated_sprite.h"

Fish::Fish(float x, float y) : Object(x, y) {
  sprite.reset(new AnimatedSprite("sprites", 0, 48, kSize, kSize, 4, 8));
  dx = (float) rand() / (float) RAND_MAX * 0.1f - 0.05f;
}

void Fish::update(unsigned int elapsed, float vx, float vy) {
  Object::update(elapsed, vx + dx, vy);
}

void Fish::draw(Graphics& graphics) {
  SDL_RendererFlip flip = dx > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2, flip);
}
