// Brenden Hoffman
// p01
// PhaserEnemy.h
#pragma once
#include "Enemy.h"

class PhaserEnemy : public Enemy {
public:
  PhaserEnemy(int startY);
  void update(float deltaTime) override;

private:
  enum Phase { APPROACH, SHOOTING, PATROLLING };
  Phase phase;

  float startY;
  float patrolDir;
  float fireCooldown;
  int burstCount;
  float burstTimer;
};
