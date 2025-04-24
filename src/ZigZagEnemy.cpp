// Brenden Hoffman
// p01
// ZigZagEnemy.cpp
#include "ZigZagEnemy.h"
#include "Constants.h"

ZigZagEnemy::ZigZagEnemy(int startY)
  : Enemy(W + 60, startY, 2.0f, RED_BULLET,
    "images/galaxian/GalaxianRedAlien.gif", 0.2f), directionY(1.0f),
    zigZagSpeed(1.0f), shootCycleTimer(0), isFiring(true), zigTimer(0.0f),
    zigInterval(1.0f)
{}

void ZigZagEnemy::update(float deltaTime) {
  rect.x -= speed;
  rect.y += directionY * zigZagSpeed;

  zigTimer += deltaTime;
  if (zigTimer >= zigInterval) {
    directionY *= -1;
    zigTimer = 0;
  }

  shootCycleTimer += deltaTime;
  if (shootCycleTimer >= 1.0f) {
    shootCycleTimer = 0;
    isFiring = true;
  } else if (shootCycleTimer >= 0.5f) {
    isFiring = false;
  }

  if (isFiring) {
    shootTimer += deltaTime;
    if (shootTimer >= fireRate) {
      shoot();
      shootTimer = 0;
    }
  }
}

bool ZigZagEnemy::shouldDespawn() const {
  return rect.x + rect.w < 0;
}
