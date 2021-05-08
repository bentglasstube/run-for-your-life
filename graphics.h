#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

class Graphics {
  public:

    Graphics();
    ~Graphics();

    static const int kWidth = 640;
    static const int kHeight = 480;
    enum FlipDirection { NONE, HORIZONTAL, VERTICAL, BOTH };

    void blit(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect, FlipDirection flip = NONE);
    void flip();
    void clear();

    void rect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);

    int get_width() { return kWidth; }
    int get_height() { return kHeight; }

    SDL_Texture* load_image(const std::string& file);

  private:

    typedef std::map<std::string, SDL_Texture*> TextureMap;
    TextureMap textures;
    SDL_Window* window;
    SDL_Renderer* renderer;
};
