#include "seal.h"

#include <math.h>

#include "animated_sprite.h"
#include "game_screen.h"

namespace {
  const int kWidth = 48;
  const int kHeight = 32;
  const int kBarkInterval = 1500;

  const float kMaxAcc = 0.00075f;
  const float kMaxVel = 0.25f;
}

Seal::Seal(float x, float y) : Object(x, y), vx(0), vy(0), ax(0), ay(0), bark_timer(kBarkInterval - 10) {
  walking.reset(new AnimatedSprite("sprites", 0, 48, kWidth, kHeight, 4, 8));
  swimming.reset(new AnimatedSprite("sprites", 64, 32, 32, 16, 4, 8));
}

float __clip(const float vel, const float max) {
  if (vel > max) return max;
  if (vel < -max) return -max;
  return vel;
}

void Seal::update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float dx, const float dy) {
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

  bark_timer += elapsed;
  if (bark_timer > kBarkInterval) {
    bark_timer -= kBarkInterval;
    audio.play_sample("bark");
  }

  Object::update(elapsed, audio, t, dx - vx, dy - vy);
}

void Seal::draw(Graphics& graphics, const Map::Terrain t) {
  SDL_RendererFlip flip = facing_left() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  if (t == Map::WATER) {
    swimming->draw(graphics, x - kWidth / 2, y - kHeight / 2, flip);
  } else {
    walking->draw(graphics, x - kWidth / 2, y - kHeight / 2, flip);
  }
}

void Seal::collide(Player& player, Audio& audio) {
  player.kill();
  audio.play_sample("eaten");
}
