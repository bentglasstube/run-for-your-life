#include "game_screen.h"

#include <boost/format.hpp>
#include <math.h>

#include "audio.h"
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

  distance = 0.0f;

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

  distance += vy;

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    boost::shared_ptr<Object> obj = *i;
    obj->update(elapsed, vx, vy);

    bool erase = false;

    if (obj->get_y() < 0) {
      erase = true;
    }

    if (obj->is_touching(kPlayerX, kPlayerY)) {
      player->set_vy(-vy);
    }

    if (erase) i = objects.erase(i);
    else ++i;
  }

  // TODO generate new objects
  if (rand() % 100 < elapsed) {
    int x = rand() % (Graphics::kWidth * 2) - Graphics::kWidth / 2;
    int y = Graphics::kHeight + 16;

    objects.push_back(boost::shared_ptr<Object>(new Rock(x, y)));
  }

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  // TODO this doesn't fucking work at all
  /*
  int yo = fmodf(distance * 16, 16.0f);
  for (int y = 0; y <= Graphics::kHeight; y += 16) {
    for (int x = 0; x < Graphics::kWidth; x += 16) {
      Uint8 c = perlin.GetValue(x, y - yo + floor(distance * 16), 0) * 64 + 128;
      graphics.rect(x, y - yo, 16, 16, c, c, 255);
    }
  }
  */

  player->draw(graphics, kPlayerX - 8, kPlayerY - 8);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    (*i)->draw(graphics);
  }

  text->draw(graphics, boost::str(boost::format("Distance: % 9um") % distance), 0, 0);
  int score = 123456;
  text->draw(graphics, boost::str(boost::format("% 9u") % score), Graphics::kWidth, 0, Text::Alignment::RIGHT);

}
