#include "player.h"

namespace {
  const float kAccelY = 0.0005f;
  const float kMaxVel = 0.2f;
}

Player::Player() : ax(0), vx(0), vy(0) {
  sprite.reset(new Sprite("sprites", 0, 0, kSize, kSize));
}

float _clip_vel(float vel, float max) {
  if (vel > max) return max;
  if (vel < -max) return -max;
  return vel;
}

void Player::update(unsigned int elapsed, Map::Terrain terrain) {
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

  vx = _clip_vel(vx + ax * elapsed, kMaxVel);
  vy = _clip_vel(vy + kAccelY * elapsed, kMaxVel);
}

void Player::draw(Graphics& graphics, int x, int y) {
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2);
}

