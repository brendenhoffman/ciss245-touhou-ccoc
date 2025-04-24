// Brenden Hoffman
// p01
// Bomber.h
#pragma once
#include "Enemy.h"

class Bomber : public Enemy {
public:
  Bomber();
  void update(float deltaTime) override;
  bool shouldDespawn() const override;

private:
  int cycles;
};
