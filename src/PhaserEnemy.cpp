// Brenden Hoffman
// p01
// PhaserEnemy.cpp
#include <cmath>
#include <cstdlib>
#include "PhaserEnemy.h"
#include "Constants.h"

PhaserEnemy::PhaserEnemy(int startY)
  : Enemy(W + 60, startY, 2.5f, RED_BULLET,
    "images/galaxian/GalaxianPurpleAlien.gif", 0.2f), phase(APPROACH),
    startY(startY), patrolDir(1.0f), fireCooldown(0)
{
  health = 7;
}

void PhaserEnemy::update(float deltaTime) {
  switch (phase) {
    case APPROACH:
      rect.x -= speed;
      if (rect.x <= W - 60) {
        phase = SHOOTING;
        fireCooldown = 0;
      }
      break;

    case SHOOTING:
      burstTimer += deltaTime;

      if (burstCount < 3 && burstTimer >= 0.2f) {
        float baseAngle = M_PI;
        float spread = M_PI / 6;
        float angles[] = {
          baseAngle - spread,
          baseAngle - spread / 2,
          baseAngle,
          baseAngle + spread / 2,
          baseAngle + spread
        };

        for (float angle : angles) {
          float bx = rect.x;
          float by = rect.y + rect.h / 2;
          float speed = cos(angle) * -5;
          bullets.push_back(Bullet(bx, by, 5, speed, angle, bulletColor));
        }

        burstCount++;
        burstTimer = 0;
      }

      if (burstCount >= 3) {
        burstCount = 0;
        burstTimer = 0;
        phase = PATROLLING;
      }
      break;

    case PATROLLING:
      rect.y += patrolDir;
      if (rect.y <= startY - 80 || rect.y >= startY + 80) {
        patrolDir *= -1;
        if (rand() % 3 != 0) {
          phase = SHOOTING;
          fireCooldown = 0;
        }
      }
      break;
  }

  shootTimer += deltaTime;
}
