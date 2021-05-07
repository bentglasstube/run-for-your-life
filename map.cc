#include "map.h"

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

namespace {
  const int kDrawScale = 4;
  const float kNoiseScale = 500.0f;
}

Map::Map() : xo(0), yo(0), seed(rand() % 256) {}

Map::Terrain Map::get(int x, int y) {
  const float nx = (x + xo) / kDrawScale * kDrawScale / kNoiseScale;
  const float ny = (y + yo) / kDrawScale * kDrawScale / kNoiseScale;

  const float n = stb_perlin_fbm_noise3(nx, ny, seed, 2.0f, 0.5f, 6);

  const float snow = ny * kNoiseScale / 50000.0f;
  const float ice  = ny * kNoiseScale / 125000.0f - 0.75f;

  if (n > snow) return Map::SNOW;
  if (n > ice) return Map::ICE;
  return Map::WATER;
}

void Map::draw(Graphics& graphics) {
  const int dx = xo % kDrawScale + (xo < 0 ? kDrawScale : 0);
  const int dy = yo % kDrawScale;

  for (int y = -dy; y <= Graphics::kHeight; y += kDrawScale) {
    for (int x = -dx; x <= Graphics::kWidth; x += kDrawScale) {
      Terrain t = get(x, y);

      switch (t) {
        case SNOW:
          graphics.rect(x, y, kDrawScale, kDrawScale, 255, 255, 255);
          break;
        case ICE:
          graphics.rect(x, y, kDrawScale, kDrawScale, 95, 205, 228);
          break;
        case WATER:
          graphics.rect(x, y, kDrawScale, kDrawScale, 91, 110, 225);
          break;
      }
    }
  }
}
