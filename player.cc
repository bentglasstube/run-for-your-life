#include "player.h"

#include "animated_sprite.h"

namespace {
  const float kAccelY = 0.0005f;
  const float kMaxVel = 0.2f;
}

Player::Player() : ax(0), vx(0), vy(0), tripping(false), dead(false), score(0), last_tile(Map::SNOW) {
  walking.reset(new AnimatedSprite("sprites", 0, 0, kSize, kSize, 3, 16, AnimatedSprite::BOUNCE));
  swimming.reset(new AnimatedSprite("sprites", 0, 32, kSize, kSize / 2, 2, 16));
  sliding.reset(new Sprite("sprites", 96, 0, kSize, kSize));
}

float _clip_vel(const float vel, const float max) {
  if (vel > max) return max;
  if (vel < -max) return -max;
  return vel;
}

void Player::update(const unsigned int elapsed, const Map::Terrain terrain, Audio& audio) {
  if (dead) return;

  float friction = 0.0;
  switch (terrain) {
    case Map::SNOW:
      friction = 0.995f;
      break;
    case Map::ICE:
      friction = 0.999f;
      break;
    case Map::WATER:
      friction = 0.990f;
      break;
  }

  for (unsigned int i = 0; i < elapsed; ++i) {
    vx *= friction;
    vy *= friction;
  }

  if (tripping) {
    if (terrain == Map::WATER || vy < 0.01f) tripping = false;
  } else {
    vx = _clip_vel(vx + ax * elapsed, kMaxVel);
    vy = _clip_vel(vy + kAccelY * elapsed, kMaxVel);
  }

  if (terrain == Map::WATER && last_tile != Map::WATER) audio.play_sample("splash");
  last_tile = terrain;
}

void Player::draw(Graphics& graphics, const Map::Terrain terrain, const int x, const int y) {
  if (dead) return;

  if (terrain == Map::WATER) {
    swimming->draw(graphics, x - kSize / 2, y - kSize / 2);
  } else if (tripping) {
    sliding->draw(graphics, x - kSize / 2, y - kSize / 2);
  } else {
    walking->draw(graphics, x - kSize / 2, y - kSize / 2);
  }
}

void Player::trip() {
  if (!tripping) {
    tripping = true;
    vy *= 1.5;
  }
}
