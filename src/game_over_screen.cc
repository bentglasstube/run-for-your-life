#include "game_over_screen.h"

#include <boost/format.hpp>
#include <stdio.h>
#include <string.h>

#include "game_screen.h"

void GameOverScreen::init() {
  backdrop.reset(new Backdrop("gameover"));
  text.reset(new Text("text"));

  place = 99;
  initials_pos = 0;

  FILE* fd = fopen("content/scores.txt", "r");
  if (fd) {
    for (int i = 0; i < 10; ++i) {
      char initials[4];
      int s;

      fscanf(fd, "%s%d\n", &initials, &s);

      if (score > s && place > 10) {
        fprintf(stderr, "Congrats, %u place\n", i);
        place = i;
        strcpy(top_scores[i].initials, "___");
        ++i;
      }

      if (i < 10) {
        strcpy(top_scores[i].initials, initials);
        top_scores[i].score = s;
      }
    }
    fclose(fd);
  } else {
    fprintf(stderr, "Unable to read high score file\n");
  }
}

bool GameOverScreen::update(Input& input, Audio&, Graphics&, unsigned int) {
  if (entering_name()) {
    top_scores[place].initials[initials_pos] = initial;

    if (input.key_pressed(SDLK_a)) {
      initial++;
      if (initial == '[') initial = 'A';
    } else if (input.key_pressed(SDLK_d)) {
      initial = 'A';
      ++initials_pos;

      if (initials_pos == 3) {
        FILE* fd = fopen("content/scores.txt", "w");
        if (fd) {
          for (int i = 0; i < 10; ++i) {
            fprintf(fd, "%3s %d\n", top_scores[i].initials, top_scores[i].score);
          }
          fclose(fd);
        } else {
          fprintf(stderr, "Unable to write to score file\n");
        }
      }
    }
  } else {
    if (input.key_pressed(SDLK_a)) {
      replay = true;
      return false;
    }
    if (input.key_pressed(SDLK_d)) {
      replay = false;
      return false;
    }
  }

  return true;
}

void GameOverScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  for (int i = 0; i < 5; ++i) {
    text->draw(graphics, boost::str(boost::format("%2u %3s %9u") % (i + 1) % top_scores[i].initials % top_scores[i].score), 192, 208 + 16 * i);
    text->draw(graphics, boost::str(boost::format("%2u %3s %9u") % (i + 6) % top_scores[i + 5].initials % top_scores[i + 5].score), 320, 208 + 16 * i);
  }

  if (entering_name()) {
    text->draw(graphics, "Great score! Enter your initials", 320, 416, Text::CENTER);
  } else {
    text->draw(graphics, "A: retry   D: quit", 320, 416, Text::CENTER);
  }
}

Screen* GameOverScreen::next_screen() {
  return replay ? new GameScreen() : NULL;
}

std::string GameOverScreen::get_music_track() {
  return "";
}

void GameOverScreen::set_score(int _score) {
  score = _score;
}

bool GameOverScreen::entering_name() {
  return place < 10 && initials_pos < 3;
}
