#include "game_screen.h"

#include <boost/format.hpp>
#include <math.h>

#include "audio.h"
#include "fish.h"
#include "graphics.h"
#include "input.h"
#include "rock.h"
#include "seal.h"

#define ISA(obj, type) boost::dynamic_pointer_cast<type>(obj)

namespace {
  const float kPlayerAccel = 0.0005f;
  const int kSpawnInterval = 100;
}

void GameScreen::init() {
  player.reset(new Player());
  text.reset(new Text("text"));

  distance = x_offset = 0.0f;

  objects = ObjectSet();
}

bool GameScreen::update(Input& input, Audio&, Graphics&, unsigned int elapsed) {
  if (dead) return true;

  float ax = 0.0f;
  if (input.key_held(SDLK_a)) ax -= kPlayerAccel;
  if (input.key_held(SDLK_d)) ax += kPlayerAccel;
  player->set_ax(ax);

  map.set_offsets(x_offset, distance);

  player->update(elapsed, map.get(kPlayerX, kPlayerY));

  float vx = player->get_vx();
  float vy = player->get_vy();

  x_offset += vx * elapsed;
  distance += vy * elapsed;

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    boost::shared_ptr<Object> obj = *i;

    bool keep = obj->update(elapsed, map.get(obj->get_x(), obj->get_y()), vx, vy);

    if (obj->get_y() < -32) {
      keep = false;
    } else if (obj->is_touching(kPlayerX, kPlayerY)) {
      if (ISA(obj, Rock)) {
        player->trip();
        score -= 25;
        // TODO play bump sound
        // TODO lose control

      } else if (ISA(obj, Fish)) {
        keep = false;
        score += 100;
        // TODO play yum sound

      } else if (ISA(obj, Seal)) {
        dead = true;
        // TODO play game over sound
      }
    }

    if (keep) ++i;
    else i = objects.erase(i);
  }

  spawn_timer += elapsed;
  if (spawn_timer > kSpawnInterval) {
    spawn_timer -= kSpawnInterval;

    int x = rand() % (Graphics::kWidth * 2) - Graphics::kWidth / 2;
    int y = Graphics::kHeight + 16;

    int r = rand() % 32;
    hist[r]++;

    switch (map.get(x, y)) {
      case Map::SNOW:
        if (r < 24) spawn_rock(x, y);
        else if (r < 28) spawn_fish(x, y);
        break;

      case Map::ICE:
        if (r < 16) spawn_rock(x, y);
        else if (r < 28) spawn_fish(x, y);
        else if (r < 29) spawn_seal(x, y);
        break;

      case Map::WATER:
        if (r < 2) spawn_seal(x, y);
        break;
    }
  }

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map.draw(graphics);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    boost::shared_ptr<Object> obj = *i;
    obj->draw(graphics, map.get(obj->get_x(), obj->get_y()));
  }

  if (!dead) player->draw(graphics, map.get(kPlayerX, kPlayerY), kPlayerX, kPlayerY);

  text->draw(graphics, boost::str(boost::format("% 9u") % (score + (int)(distance / 100))), Graphics::kWidth, 0, Text::Alignment::RIGHT);

  for (int i = 0; i < 32; ++i) {
    graphics.rect(0, 4 * i, hist[i], 4, 255, 0, 0);
  }

  graphics.rect(0, 132, hist[32], 4, 132, 126, 135);
  graphics.rect(0, 136, hist[33], 4, 223, 113, 38);
  graphics.rect(0, 140, hist[34], 4, 50, 60, 57);
}

void GameScreen::spawn_rock(int x, int y){
  objects.push_back(boost::shared_ptr<Object>(new Rock(x, y)));
  hist[32]++;
}

void GameScreen::spawn_fish(int x, int y){
  objects.push_back(boost::shared_ptr<Object>(new Fish(x, y)));
  hist[33]++;
}

void GameScreen::spawn_seal(int x, int y){
  objects.push_back(boost::shared_ptr<Object>(new Seal(x, y)));
  hist[34]++;
}
