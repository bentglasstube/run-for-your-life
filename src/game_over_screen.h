#pragma once

#include <memory>

#include "audio.h"
#include "backdrop.h"
#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "text.h"

class GameOverScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track();

    void set_score(int _score);

  private:

    typedef struct {
      char initials[3];
      int score;
    } HighScore;

    bool replay;
    int score, place, initials_pos;
    char initial = 'A';

    HighScore top_scores[10];
    std::string format_score(int n, HighScore score);

    std::unique_ptr<Backdrop> backdrop;
    std::unique_ptr<Text> text;

    bool entering_name();
};
