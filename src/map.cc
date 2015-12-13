#include "map.h"

#include "random.h"

namespace {
  const int kDrawScale = 4;
  const float kNoiseScale = 500.0f;
}

Map::Map() : xo(0), yo(0) {
  Random r = Random();
  seed = r.randf(0.0f, 1.0f);
}

Map::Terrain Map::get(int x, int y) {
  // Integer division here aligns the values to prevent flickering
  const float nx = (x + xo) / kDrawScale * kDrawScale / kNoiseScale;
  const float ny = (y + yo) / kDrawScale * kDrawScale / kNoiseScale;

  const float n = perlin.GetValue(nx, ny, seed);

  const float snow = ny * kNoiseScale / 50000.0f;
  const float ice  = ny * kNoiseScale / 125000.0f - 0.75f;

  if (n > snow) return Map::SNOW;
  if (n > ice) return Map::ICE;
  return Map::WATER;
}

void Map::draw(Graphics& graphics) {
  const int dx = fmodf(xo * kDrawScale, kDrawScale);
  const int dy = fmodf(yo * kDrawScale, kDrawScale);

  for (int y = 0; y <= Graphics::kHeight; y += kDrawScale) {
    for (int x = 0; x <= Graphics::kWidth; x += kDrawScale) {
      int rx = x - dx;
      int ry = y - dy;

      switch (get(rx, ry)) {
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
