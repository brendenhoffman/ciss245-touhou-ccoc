// Brenden Hoffman
// p01
// BossEnemy.h
#pragma once
#include "Enemy.h"

class BossEnemy : public Enemy {
public:
  BossEnemy();
  void update(float deltaTime) override;

private:
  enum Phase {
    ENTERING,
    IDLE,
    ATTACK_WIDE_BURST,
    ATTACK_WALL,
    ATTACK_RANDOM_BIG,
    ATTACK_TRIPLE,
  };

  Phase currentPhase;
  float phaseTimer;
  float attackTimer;
  int burstShots;
  int bigShotsFired;
  float wallY;

  void startRandomAttack();
  void fireWideBurst();
  void fireWall();
  void fireRandomBig();
  void fireTriple();
};
