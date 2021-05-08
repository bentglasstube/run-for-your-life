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

    std::unique_ptr<Screen> screen;
    std::unique_ptr<Graphics> graphics;
    Audio audio;
    Input input;

    unsigned int last_update;
};
