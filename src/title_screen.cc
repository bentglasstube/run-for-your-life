#include "title_screen.h"

#include "audio.h"
#include "game_screen.h"
#include "graphics.h"
#include "input.h"

void TitleScreen::init() {
  text.reset(new Text("text"));
}

bool TitleScreen::update(Input& input, Audio&, Graphics&, unsigned int) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) {
  text->draw(graphics, "Press any key", 320, 264, Text::CENTER);
}

Screen* TitleScreen::next_screen() {
  return new GameScreen();
}
