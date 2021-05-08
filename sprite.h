#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "graphics.h"

class Sprite {
  public:

    Sprite(const std::string& file, int x, int y, int w, int h);
    virtual ~Sprite() {}

    virtual void draw(Graphics& graphics, int x, int y, Graphics::FlipDirection flip = Graphics::NONE);

  protected:
    SDL_Rect rect;

  private:
    std::string file;
};
