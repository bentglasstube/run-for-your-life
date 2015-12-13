#include "map.h"

namespace {
  const int kDrawScale = 4;
  const float kNoiseScale = 500.0f;
}

Map::Map() : xo(0), yo(0) {
  seed = rand();
}

Map::Terrain Map::get(int x, int y) {
  float nx = (x / kDrawScale * kDrawScale + xo) / kNoiseScale;
  float ny = (y / kDrawScale * kDrawScale + yo) / kNoiseScale;

  const float n = perlin.GetValue(nx, ny, seed);

  // TODO determine formulas for increasing difficulty

  if (n > 0) return Map::SNOW;
  if (n > -0.75) return Map::ICE;
  return Map::WATER;
}

void Map::draw(Graphics& graphics) {
  const int dx = fmodf(xo * kDrawScale, kDrawScale);
  const int dy = fmodf(yo * kDrawScale, kDrawScale);

  for (int y = 0; y <= Graphics::kHeight; y += kDrawScale) {
    for (int x = 0; x <= Graphics::kWidth; x += kDrawScale) {
      int rx = x - dx;
      int ry = y - dy;

      Terrain t = get(x, y);

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
