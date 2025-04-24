// Brenden Hoffman
// p01
// Bullet.cpp
#include "Constants.h"
#include "Bullet.h"

Color getBulletColor(BulletColor color) {
  switch (color) {
    case RED_BULLET:   return RED;
    case BLUE_BULLET:  return BLUE;
    case GREEN_BULLET: return GREEN;
    default:           return WHITE;
  }
}

Bullet::Bullet(int x, int y, int radius, float speed, float angle, BulletColor color)
  : x(x), y(y), radius(radius), speed(speed), angle(angle), color(getBulletColor(color)) {
  speedX = speed * cos(angle);
  speedY = speed * sin(angle);
}

void Bullet::update() {
  x += speedX;
  y += speedY;
}

void Bullet::draw(Surface& surface) const {
  surface.put_circle(x, y, radius, color);
}

bool Bullet::isOffScreen() const {
  return x < 0 || x > W || y < 0 || y > H;
}

