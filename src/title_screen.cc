#include "title_screen.h"

#include "animated_sprite.h"
#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "text.h"

void TitleScreen::init() {
  text.reset(new Text("text"));
  blob.reset(new AnimatedSprite("sprites", 0, 0, 16, 16, 3, 8, AnimatedSprite::BOUNCE));
  heart.reset(new Sprite("sprites", 0, 16, 16, 16));
}

bool TitleScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) {
  blob->draw(graphics, 312, 232);
  heart->draw(graphics, 280, 232);
  heart->draw(graphics, 344, 232);

  text->draw(graphics, "Press any key", 320, 264, Text::CENTER);
}
