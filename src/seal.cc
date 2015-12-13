#include "seal.h"

#include <math.h>

#include "animated_sprite.h"
#include "game_screen.h"

namespace {
  const int kWidth = 48;
  const int kHeight = 32;

  const float kMaxAcc = 0.00075f;
  const float kMaxVel = 0.25f;
}

Seal::Seal(float x, float y) : Object(x, y) {
  sprite.reset(new AnimatedSprite("sprites", 0, 96, kWidth, kHeight, 4, 8));
}

float __clip(const float vel, const float max) {
  if (vel > max) return max;
  if (vel < -max) return -max;
  return vel;
}

bool Seal::update(const unsigned int elapsed, const Map::Terrain t, const float dx, const float dy) {
  float friction = 0.0;
  switch (t) {
    case Map::SNOW:
      friction = 0.990f;
      break;
    case Map::ICE:
      friction = 0.995f;
      break;
    case Map::WATER:
      friction = 0.999f;
      break;
  }

  for (unsigned int i = 0; i < elapsed; ++i) {
    vx *= friction;
    vy *= friction;
  }

  ax = GameScreen::kPlayerX < x ? -kMaxAcc : kMaxAcc;
  ay = GameScreen::kPlayerY < y ? -kMaxAcc : kMaxAcc;

  vx = __clip(vx + ax * elapsed, kMaxVel);
  vy = __clip(vy + ay * elapsed, kMaxVel);

  return Object::update(elapsed, t, dx - vx, dy - vy);
}

void Seal::draw(Graphics& graphics) {
  SDL_RendererFlip flip = facing_left() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  sprite->draw(graphics, x - kWidth / 2, y - kHeight / 2, flip);
}
