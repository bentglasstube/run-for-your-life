#include "random.h"

Random::Random() {
  std::random_device rd;
  mt = std::mt19937(rd());
}

float Random::randf(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(mt);
}

int Random::rand(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}

unsigned int Random::urand(unsigned int min, unsigned int max) {
  std::uniform_int_distribution<unsigned int> dist(min, max);
  return dist(mt);
}

bool Random::randb() {
  return rand(0, 1) == 1;
}
