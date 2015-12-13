#pragma once

#include <random>

class Random {
  public:

    Random();

    float randf(float min, float max);
    int rand(int min, int max);
    unsigned int urand(unsigned int min, unsigned int max);
    bool randb();

  private:

    std::mt19937 mt;
};
