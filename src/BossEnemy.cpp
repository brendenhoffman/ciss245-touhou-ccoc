// Brenden Hoffman
// p01
// BossEnemy.cpp
#include <cmath>
#include <cstdlib>
#include "BossEnemy.h"
#include "Constants.h"

BossEnemy::BossEnemy()
  : Enemy(W + 100, H / 2, 2.0f, RED_BULLET,
    "images/galaxian/GalaxianFlagship.gif", 0.2f), currentPhase(ENTERING),
    phaseTimer(0), attackTimer(0), burstShots(0), bigShotsFired(0)
{
  health = 50;
}

void BossEnemy::update(float deltaTime) {
  phaseTimer += deltaTime;
  attackTimer += deltaTime;

  switch (currentPhase) {
    case ENTERING:
      rect.x -= speed;
      if (rect.x <= W - 120) {
        rect.x = W - 120;
        currentPhase = IDLE;
        phaseTimer = 0;
      }
      break;

    case IDLE:
      if (phaseTimer >= 1.0f) {
        startRandomAttack();
        phaseTimer = 0;
        attackTimer = 0;
      }
      break;

    case ATTACK_WIDE_BURST:
      if (attackTimer >= 0.2f && burstShots < 5) {
        float base = M_PI;
        float spread = M_PI / 3;
        for (int i = 0; i < 7; ++i) {
          float angle = base - spread/2 + i * (spread / 6);
          float speed = cos(angle) * -5;
          bullets.push_back(Bullet(rect.x, rect.y + rect.h / 2, 5, speed, angle, bulletColor));
        }
        attackTimer = 0;
        burstShots++;
      } else if (burstShots >= 5) {
        currentPhase = IDLE;
        burstShots = 0;
        phaseTimer = 0;
      }
      break;

    case ATTACK_WALL:
      if (attackTimer >= 0.1f) {
        if (wallY <= H - 24) {
          bullets.push_back(Bullet(rect.x, wallY, 5, 4, M_PI, bulletColor));
          wallY += (H - 48) / 19.0f;
          attackTimer = 0;
        } else {
          currentPhase = IDLE;
          phaseTimer = 0;
        }
      }
      break;

    case ATTACK_RANDOM_BIG:
      if (attackTimer >= 0.4f && bigShotsFired < 8) {
        float base = M_PI;
        float spread = M_PI / 3;
        float angle = base - spread / 2 + static_cast<float>(rand()) / RAND_MAX * spread;
        bullets.push_back(Bullet(rect.x, rect.y + rect.h / 2, 10, 3, angle, bulletColor));
        attackTimer = 0;
        bigShotsFired++;
      } else if (bigShotsFired >= 8) {
        bigShotsFired = 0;
        currentPhase = IDLE;
        phaseTimer = 0;
      }
      break;

    case ATTACK_TRIPLE:
      if (attackTimer >= fireRate && phaseTimer <= 0.5f) {
        float offset = 10;
        for (int i = -1; i <= 1; ++i) {
          bullets.push_back(Bullet(rect.x, rect.y + rect.h / 2 + i * offset, 5, 5, M_PI, bulletColor));
        }
        attackTimer = 0;
      } else if (phaseTimer > 0.8f) {
        currentPhase = IDLE;
        phaseTimer = 0;
      }
      break;
  }

  shootTimer += deltaTime;
}

void BossEnemy::startRandomAttack() {
  int choice = rand() % 4;
  currentPhase = static_cast<Phase>(ATTACK_WIDE_BURST + choice);
  if (currentPhase == ATTACK_WALL) {
    wallY = 24;
  }
}
