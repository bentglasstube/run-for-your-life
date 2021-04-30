#include "game_over_screen.h"

#include <stdio.h>
#include <string.h>

#include <iomanip>
#include <sstream>

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

      int count = fscanf(fd, "%3s%d\n", initials, &s);
      if (count < 2) break;

      if (score > s && place > 10) {
        fprintf(stderr, "Congrats, %d - %u place\n", score, i);
        place = i;
        strcpy(top_scores[i].initials, "___");
        top_scores[i].score = score;
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

std::string GameOverScreen::format_score(int n, HighScore score) {
  std::ostringstream out;
  out << std::setfill(' ') << std::setw(2) << n << ' ';
  out << std::setw(3) << score.initials << ' ';
  out << std::setw(9) << score.score;
  return out.str();
}

void GameOverScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  for (int i = 0; i < 5; ++i) {
    text->draw(graphics, format_score(i, top_scores[i]), 184, 208 + 16 * i);
    text->draw(graphics, format_score(i + 5, top_scores[i + 5]), 320, 208 + 16 * i);
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
