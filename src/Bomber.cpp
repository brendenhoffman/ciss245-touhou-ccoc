// Brenden Hoffman
// p01
// Bomber.cpp
#include <cstdlib>
#include "Bomber.h"
#include "Constants.h"

Bomber::Bomber()
  : Enemy(W + 60, rand() % (H - 60), 3.0f, BLUE_BULLET,
    "images/galaxian/GalaxianAquaAlien.gif", 0.2f), cycles(0)
{}

void Bomber::update(float deltaTime) {
  rect.x -= speed;

  if (rect.x + rect.w < 0) {
    cycles++;
    if (cycles < 5) {
      rect.x = W + 60;
      rect.y = rand() % (H - 60);
    }
  }
}

bool Bomber::shouldDespawn() const {
  return (cycles >= 5 && rect.x + rect.w < 0);
}
