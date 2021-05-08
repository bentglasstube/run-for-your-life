#include "fish.h"

#include "animated_sprite.h"

Fish::Fish(float x, float y) : Object(x, y) {
  int c = rand() % 64;
  if      (c >= 31) color = 0;
  else if (c >= 15) color = 1;
  else if (c >=  7) color = 2;
  else if (c >=  3) color = 3;
  else if (c >=  1) color = 4;
  else              color = 5;

  sprite.reset(new AnimatedSprite("sprites", 64 * (color % 3), 80 + 16 * (color / 3), kSize, kSize, 4, 8));

  dx = 0.025f + 0.005f * color;
  if (rand() % 2 == 1) dx *= -1;

  dy = (float) rand() / (float) RAND_MAX * 0.05f - 0.025;
}

void Fish::update(const unsigned int elapsed, Audio& audio, const Map::Terrain t, const float vx, const float vy) {
  float mx = dx;
  float my = dy;

  switch (t) {
    case Map::SNOW:
      break;
    case Map::ICE:
      mx *= 1.5;
      my *= 1.5;
      break;
    case Map::WATER:
      audio.play_sample("splash");
      dead = true;
      break;
  }

  return Object::update(elapsed, audio, t, vx + mx, vy + my);
}

void Fish::draw(Graphics& graphics, const Map::Terrain) {
  Graphics::FlipDirection flip = dx > 0 ? Graphics::HORIZONTAL : Graphics::NONE;
  sprite->draw(graphics, x - kSize / 2, y - kSize / 2, flip);
}

void Fish::collide(Player& player, Audio& audio) {
  player.add_points(value());
  audio.play_sample("yum");
  dead = true;
}

int Fish::value() {
  switch (color) {
    case 0: return 10;
    case 1: return 25;
    case 2: return 50;
    case 3: return 100;
    case 4: return 250;
    case 5: return 500;
  }

  return 0;
}
