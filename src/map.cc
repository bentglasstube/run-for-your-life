#include "map.h"

namespace {
  const int kDrawScale = 4;
  const float kNoiseScale = 500.0f;
}

Map::Map() {
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
          graphics.rect(rx, ry, kDrawScale, kDrawScale, 224, 225, 255);
          break;
        case WATER:
          graphics.rect(rx, ry, kDrawScale, kDrawScale, 64, 64, 255);
          break;
      }
    }
  }

}
