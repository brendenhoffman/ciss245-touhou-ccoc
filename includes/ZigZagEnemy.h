// Brenden Hoffman
// p01
// ZigZagEnemy.h
#pragma once
#include "Enemy.h"

class ZigZagEnemy : public Enemy {
public:
  ZigZagEnemy(int startY);
  void update(float deltaTime) override;
  bool shouldDespawn() const override;

private:
  float directionY;
  float zigZagSpeed;
  float shootCycleTimer;
  bool isFiring;
  float zigTimer;
  float zigInterval;
};
