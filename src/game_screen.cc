#include "game_screen.h"

#include <boost/format.hpp>
#include <math.h>

#include "audio.h"
#include "fish.h"
#include "graphics.h"
#include "input.h"
#include "rock.h"

#define ISA(obj, type) boost::dynamic_pointer_cast<type>(obj)

namespace {
  const float kPlayerAccel = 0.0005f;

  const float kPlayerX = Graphics::kWidth / 2;
  const float kPlayerY = Graphics::kHeight / 2;
}

void GameScreen::init() {
  player.reset(new Player());
  text.reset(new Text("text"));

  distance = x_offset = 0.0f;

  objects = ObjectSet();
}

bool GameScreen::update(Input& input, Audio&, Graphics&, unsigned int elapsed) {
  float ax = 0.0f;
  if (input.key_held(SDLK_a)) ax -= kPlayerAccel;
  if (input.key_held(SDLK_d)) ax += kPlayerAccel;
  player->set_ax(ax);

  player->update(elapsed, map.get(kPlayerX + x_offset, kPlayerY + distance));

  float vx = player->get_vx();
  float vy = player->get_vy();

  x_offset += vx * elapsed;
  distance += vy * elapsed;

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    boost::shared_ptr<Object> obj = *i;

    bool keep = obj->update(elapsed, map.get(obj->get_x() + x_offset, obj->get_y() + distance), vx, vy);

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

      }
    }

    if (keep) ++i;
    else i = objects.erase(i);
  }

  if (rand() % 100 < elapsed) {
    int x = rand() % (Graphics::kWidth * 2) - Graphics::kWidth / 2;
    int y = Graphics::kHeight + 16;

    int r = rand() % 32;
    switch (map.get(x + x_offset, y + distance)) {
      case Map::SNOW:
        if (r < 24) spawn_rock(x, y);
        if (r < 28) spawn_fish(x, y);
        break;

      case Map::ICE:
        if (r < 12) spawn_rock(x, y);
        if (r < 16) spawn_fish(x, y);
        if (r < 18) spawn_seal(x, y);
        break;

      case Map::WATER:
        if (r < 4) spawn_seal(x, y);
        break;
    }
  }

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map.draw(graphics, x_offset, distance);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    (*i)->draw(graphics);
  }

  player->draw(graphics, map.get(kPlayerX + x_offset, kPlayerY + distance), kPlayerX, kPlayerY);

  text->draw(graphics, boost::str(boost::format("% 9u") % (score + (int)(distance / 100))), Graphics::kWidth, 0, Text::Alignment::RIGHT);
}

void GameScreen::spawn_rock(int x, int y){
  objects.push_back(boost::shared_ptr<Object>(new Rock(x, y)));
}

void GameScreen::spawn_fish(int x, int y){
  objects.push_back(boost::shared_ptr<Object>(new Fish(x, y)));
}

void GameScreen::spawn_seal(int, int){
  // objects.push_back(boost::shared_ptr<Object>(new Fish(x, y)));
}
