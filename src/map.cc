#include "map.h"

namespace {
  const int kDrawScale = 4;
  const float kNoiseScale = 500.0f;
}

Map::Map() {
  // TODO use masking or something to make sprites less terrible?
  sprites[SNOW]  = boost::shared_ptr<Sprite>(new Sprite("sprites",  0, 0, kDrawScale, kDrawScale));
  sprites[ICE]   = boost::shared_ptr<Sprite>(new Sprite("sprites", 16, 0, kDrawScale, kDrawScale));
  sprites[WATER] = boost::shared_ptr<Sprite>(new Sprite("sprites", 32, 0, kDrawScale, kDrawScale));
}

Map::Terrain Map::get(float x, float y) {
  // TODO memoization for performance if needed

  float n = perlin.GetValue(x / kNoiseScale, y / kNoiseScale, 0);

  if (n > 0) return Map::SNOW;
  if (n > -0.75) return Map::ICE;
  return Map::WATER;
}

void Map::draw(Graphics& graphics, float dx, float dy) {
  const int xo = fmodf(dx * kDrawScale, kDrawScale);
  const int yo = fmodf(dy * kDrawScale, kDrawScale);

  for (int y = 0; y <= Graphics::kHeight; y += kDrawScale) {
    for (int x = 0; x <= Graphics::kWidth; x += kDrawScale) {
      int rx = x - xo;
      int ry = y - yo;

      Terrain t = get(rx + dx, ry + dy);

      switch (t) {
        case SNOW:
          graphics.rect(rx, ry, kDrawScale, kDrawScale, 255, 255, 255);
          break;
        case ICE:
          graphics.rect(rx, ry, kDrawScale, kDrawScale, 95, 205, 228);
          break;
        case WATER:
          graphics.rect(rx, ry, kDrawScale, kDrawScale, 91, 110, 225);
          break;
      }
    }
  }
}
