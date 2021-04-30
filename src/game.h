#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "input.h"

class Screen;

class Game {
  public:

    Game();
    ~Game();

    void loop();
    void start();
    void step();

  private:

    Graphics graphics;
    Audio audio;
    Input input;

    std::unique_ptr<Screen> screen;

    unsigned int last_update;
};
