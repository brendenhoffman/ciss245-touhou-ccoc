// Brenden Hoffman
// p01
// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <cmath>
#include "Color.h"
#include "Surface.h"
#include "GameObject.h"

enum BulletColor { RED_BULLET, BLUE_BULLET, GREEN_BULLET };

Color getBulletColor(BulletColor color);

class Bullet : public GameObject {
public:
  Bullet(int x, int y, int radius, float speed, float angle, BulletColor color);
  void update();
  void draw(Surface& surface) const;
  bool isOffScreen() const;
  int getX() const override { return x; }
  int getY() const override { return y; }
  int getWidth() const override { return radius * 2; }
  int getHeight() const override { return radius * 2; }

private:
  int x, y;
  int radius;
  float speed;
  float angle;
  float speedX, speedY;
  Color color;
};

#endif
