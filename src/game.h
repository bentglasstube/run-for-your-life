#pragma once

#include <memory>

class Screen;
class Graphics;

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    std::unique_ptr<Screen> screen;
};
