#include "player.h"

namespace {
  const float kAccelY = 0.0005f;
  const float kMaxVel = 0.2f;
}

Player::Player() : ax(0), vx(0), vy(0) {
  sprite.reset(new Sprite("sprites", 48, 0, 16, 16));
}

float _clip_vel(float vel, float max) {
  if (vel > max) return max;
  if (vel < -max) return -max;
  return vel;
}

void Player::update(unsigned int elapsed) {
  for (int i = 0; i < elapsed; ++i) vx *= 0.995f;

  vx = _clip_vel(vx + ax * elapsed, kMaxVel);
  vy = _clip_vel(vy + kAccelY * elapsed, kMaxVel);
}

void Player::draw(Graphics& graphics, int x, int y) {
  sprite->draw(graphics, x, y);
}

