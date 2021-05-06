#include "graphics.h"

Graphics::Graphics() {
  const int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

  window = SDL_CreateWindow("Run For Your Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWidth * 2, kHeight * 2, flags);
  renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // retro!
  SDL_RenderSetLogicalSize(renderer, kWidth, kHeight);
  SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Graphics::~Graphics() {
  for (TextureMap::iterator i = textures.begin(); i != textures.end(); ++i) {
    SDL_DestroyTexture(i->second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Graphics::blit(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect, const SDL_RendererFlip flip) {
  SDL_Texture* texture = load_image(file);
  SDL_RenderCopyEx(renderer, texture, srect, drect, 0, NULL, flip);
}

void Graphics::flip() {
  SDL_RenderPresent(renderer);
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void Graphics::rect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
  SDL_Rect rect = { x, y, w, h };
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::pixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderDrawPoint(renderer, x, y);
}

SDL_Texture* Graphics::load_image(const std::string& file) {
  const std::string path("content/" + file+ ".bmp");
  if (textures.count(path) == 0) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    const Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
    SDL_SetColorKey(surface, SDL_TRUE, black);

    textures[path] = SDL_CreateTextureFromSurface(renderer, surface);
  }

  return textures[path];
}
