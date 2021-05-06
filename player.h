#pragma once

#include <memory>

#include "audio.h"
#include "map.h"
#include "sprite.h"

class Player {
  public:

    static const int kSize = 32;

    Player();

    void update(const unsigned int elapsed, const Map::Terrain terrain, Audio& audio);
    void draw(Graphics& graphics, const Map::Terrain terrain, const int x, const int y);

    void trip();
    void kill() { dead = true; }
    void add_points(int points) { score += points; }

    void set_vx(float _vx) { vx = _vx; }
    void set_vy(float _vy) { vy = _vy; }
    void set_ax(float _ax) { ax = _ax; }

    float get_vx() { return vx; }
    float get_vy() { return vy; }
    float get_ax() { return ax; }

    int get_score() { return score; }
    bool alive() { return !dead; }

  private:

    float ax, vx, vy;
    bool tripping, dead;
    int score;
    Map::Terrain last_tile;

    std::unique_ptr<Sprite> walking, swimming, sliding;
};
