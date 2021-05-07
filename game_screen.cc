#include "game_screen.h"

#include <iomanip>
#include <sstream>

#include "audio.h"
#include "fish.h"
#include "floating_text.h"
#include "game_over_screen.h"
#include "graphics.h"
#include "input.h"
#include "rock.h"
#include "seal.h"

namespace {
  const float kPlayerAccel = 0.0005f;
  const int kSpawnInterval = 100;
  const int kSealInterval = 30000;
}

void GameScreen::init() {
  text.reset(new Text("text"));
  distance = x_offset = 0.0f;
  objects = ObjectSet();

  spawn_timer = 0;
  seal_timer = 20000;
}

bool GameScreen::update(Input& input, Audio& audio, Graphics&, unsigned int elapsed) {
  float ax = 0.0f;
  if (input.key_held(SDLK_a)) ax -= kPlayerAccel;
  if (input.key_held(SDLK_d)) ax += kPlayerAccel;
  player.set_ax(ax);

  map.set_offsets(x_offset, distance);

  player.update(elapsed, map.get(kPlayerX, kPlayerY), audio);

  float vx = player.get_vx();
  float vy = player.get_vy();

  if ((int)((distance + vy * elapsed) / 100) > (int)(distance / 100)) {
    player.add_points(1);
  }

  x_offset += vx * elapsed;
  distance += vy * elapsed;

  const int prev_score = player.get_score();

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    std::shared_ptr<Object> obj = *i;

    obj->update(elapsed, audio, map.get(obj->get_x(), obj->get_y()), vx, vy);
    if (obj->is_touching(kPlayerX, kPlayerY)) obj->collide(player, audio);

    if (obj->moribund() || obj->get_y() < -32) {
      i = objects.erase(i);
    } else {
      ++i;
    }
  }

  int points = player.get_score() - prev_score;
  if (points != 0) spawn_text(kPlayerX, kPlayerY - 32, points);

  spawn_timer += elapsed;
  if (spawn_timer > kSpawnInterval) {
    spawn_timer -= kSpawnInterval;

    int x = rand() % (Graphics::kWidth * 2) - Graphics::kWidth / 2;
    int y = Graphics::kHeight + 16;

    int r = rand() % 32;

    switch (map.get(x, y)) {
      case Map::SNOW:
        if (r < 24) spawn_rock(x, y);
        else if (r < 28) spawn_fish(x, y);
        break;

      case Map::ICE:
        if (r < 16) spawn_rock(x, y);
        else if (r < 28) spawn_fish(x, y);
        break;

      case Map::WATER:
        if (r < 1) spawn_seal(x, y);
        break;
    }
  }

  seal_timer += elapsed;
  if (seal_timer > kSealInterval) {
    seal_timer -= kSealInterval;
    spawn_seal((rand() % 2 == 1) ? 0 : Graphics::kWidth, kPlayerY);
  }

  return player.alive();
}

void GameScreen::draw(Graphics& graphics) {
  map.draw(graphics);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    std::shared_ptr<Object> obj = *i;
    obj->draw(graphics, map.get(obj->get_x(), obj->get_y()));
  }

  player.draw(graphics, map.get(kPlayerX, kPlayerY), kPlayerX, kPlayerY);

  std::ostringstream out;
  out << ' ' << std::setfill(' ') << std::setw(9) << player.get_score();
  text->draw(graphics, out.str(), Graphics::kWidth, 0, Text::Alignment::RIGHT);
}

Screen* GameScreen::next_screen() {
  GameOverScreen* next = new GameOverScreen();
  next->set_score(player.get_score());
  return next;
}

std::string GameScreen::get_music_track() {
  return "antarcticbreeze";
}

void GameScreen::spawn_rock(int x, int y) {
  objects.push_back(std::shared_ptr<Object>(new Rock(x, y)));
}

void GameScreen::spawn_fish(int x, int y) {
  objects.push_back(std::shared_ptr<Object>(new Fish(x, y)));
}

void GameScreen::spawn_seal(int x, int y) {
  objects.push_back(std::shared_ptr<Object>(new Seal(x, y)));
}

void GameScreen::spawn_text(int x, int y, int value) {
  objects.push_back(std::shared_ptr<Object>(new FloatingText(x, y, value)));
}
