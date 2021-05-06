#include "backdrop.h"

#include "graphics.h"

Backdrop::Backdrop(const std::string& file) : file(file) {}

void Backdrop::draw(Graphics& graphics) {
  graphics.blit(file, NULL, NULL);
}
