// Brenden Hoffman
// p01
// Upgrade.h
#pragma once
#include "GameObject.h"
#include "Surface.h"
#include "Player.h"
#include "UpgradeType.h"

class Upgrade : public GameObject {
public:
  Upgrade(int x, int y, UpgradeType type);
  void update();
  void draw(Surface& surface) const;
  bool isOffScreen() const;
  UpgradeType getType() const { return type; }

  int getX() const override { return x; }
  int getY() const override { return y; }
  int getWidth() const override { return size; }
  int getHeight() const override { return size; }

private:
  int x, y;
  int size;
  float speed;
  UpgradeType type;
};
