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

  distance += vy * elapsed;
  x_offset += vx * elapsed;

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    boost::shared_ptr<Object> obj = *i;
    obj->update(elapsed, vx, vy);

    bool erase = false;

    if (obj->get_y() < 0) {
      erase = true;
    } else if (obj->is_touching(kPlayerX, kPlayerY)) {
      if (ISA(obj, Rock)) {
        player->set_vy(-vy);
        player->set_vx(obj->get_x() > kPlayerX ? -1.0f : 1.0f);
        score -= 25;
      } else if (ISA(obj, Fish)) {
        erase = true;
        score += 100;
      }
    }

    if (erase) i = objects.erase(i);
    else ++i;
  }

  if (rand() % 100 < elapsed) {
    int x = rand() % (Graphics::kWidth * 2) - Graphics::kWidth / 2;
    int y = Graphics::kHeight + 16;

    int r = rand() % 8;
    if (r < 1) {
      objects.push_back(boost::shared_ptr<Object>(new Fish(x, y)));
    } else {
      objects.push_back(boost::shared_ptr<Object>(new Rock(x, y)));
    }
  }

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map.draw(graphics, x_offset, distance);

  player->draw(graphics, kPlayerX - 8, kPlayerY - 8);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    (*i)->draw(graphics);
  }

  text->draw(graphics, boost::str(boost::format("% 9u") % (score + (int)(distance / 100))), Graphics::kWidth, 0, Text::Alignment::RIGHT);

  // TODO remove
  char t = '?';
  switch (map.get(kPlayerX + x_offset, kPlayerY + distance)) {
    case Map::SNOW:  t = 'S'; break;
    case Map::ICE:   t = 'I'; break;
    case Map::WATER: t = 'W'; break;
  }

  text->draw(graphics, boost::str(boost::format("%c") % t), 0, 0);
}
