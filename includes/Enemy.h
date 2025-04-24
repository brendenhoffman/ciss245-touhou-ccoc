// Brenden Hoffman
// p01
// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "Color.h"
#include "Bullet.h"

class Enemy : public GameObject {
public:
  Enemy(int x, int y, float speed, BulletColor bulletColor, const char* imagePath, float fireRate = 1.0f);
  virtual void update(float deltaTime);
  virtual void shoot();
  virtual void move();
  virtual void draw(Surface& surface) const;
  bool isOffScreen() const;
  virtual ~Enemy() {}
  std::vector<Bullet>& getBullets() { return bullets; }
  bool checkBulletCollision(const std::vector<Bullet>& playerBullets);
  int getX() const override { return rect.x; }
  int getY() const override { return rect.y; }
  int getWidth() const override { return rect.w; }
  int getHeight() const override { return rect.h; }
  void takeDamage();
  int getHealth() const { return health; }
  virtual bool shouldDespawn() const { return false; }
  void setHealth(int h) { health = std::max(0, h); }

protected:
  Image sprite;
  Rect rect;
  int x, y;
  int width, height;
  float speed;
  BulletColor bulletColor;
  std::vector<Bullet> bullets;
  bool isShooting;
  float shootTimer;
  float fireRate;
  float moveTimer;
  int health;
  float spawnIFrame = 0.3f;
};

#endif

