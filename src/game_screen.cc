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

  player->update(elapsed);

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
  const int draw_scale = 4;
  const float noise_scale = 500.0f;

  const int yo = fmodf(distance * draw_scale, draw_scale);
  const int xo = fmodf(x_offset * draw_scale, draw_scale);

  for (int y = 0; y <= Graphics::kHeight; y += draw_scale) {
    for (int x = 0; x <= Graphics::kWidth; x += draw_scale) {
      float n = perlin.GetValue((x - xo + x_offset) / noise_scale, (y - yo + distance) / noise_scale, 0);

      int rx = x - xo;
      int ry = y - yo;

      if (n > 0) { // SNOW
        graphics.rect(rx, ry, draw_scale, draw_scale, 255, 255, 255);
      } else if (n > -0.75f) { // ICE
        graphics.rect(rx, ry, draw_scale, draw_scale, 224, 225, 255);
      } else {
        graphics.rect(rx, ry, draw_scale, draw_scale, 64, 64, 255);
      }
    }
  }

  player->draw(graphics, kPlayerX - 8, kPlayerY - 8);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    (*i)->draw(graphics);
  }

  text->draw(graphics, boost::str(boost::format("% 9u") % (score + (int)(distance / 100))), Graphics::kWidth, 0, Text::Alignment::RIGHT);

}
