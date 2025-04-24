#include <cmath>
#include "Enemy.h"
#include "Constants.h"
#include "Bullet.h"
#include "Image.h"

Enemy::Enemy(int x, int y, float speed, BulletColor bulletColor,
  const char* imagePath, float fireRate)
  : x(x), y(y), speed(speed), bulletColor(bulletColor), fireRate(fireRate),
    isShooting(false), shootTimer(0), moveTimer(0), health(3),
    sprite(imagePath), spawnIFrame(0.3f)
{
    rect = sprite.getRect();
    rect.x = x;
    rect.y = y;

    width = rect.w;
    height = rect.h;
}

void Enemy::update(float deltaTime) {
  if (spawnIFrame > 0.0f) {
    spawnIFrame -= deltaTime;
  }
  moveTimer += deltaTime;
  move();
  shootTimer += deltaTime;

  if (isShooting && shootTimer >= fireRate) {
      shoot();
      shootTimer = 0;
  }
}

void Enemy::move() {
  y -= speed;
}

void Enemy::shoot() {
  int bulletX = rect.x;
  int bulletY = rect.y + rect.h / 2;

  float speed = -5;
  float angle = 0;

  bullets.push_back(Bullet(bulletX, bulletY, 5, speed, angle, bulletColor));
}

void Enemy::draw(Surface& surface) const {
  surface.put_image(sprite, rect);
  for (const Bullet& bullet : bullets) {
    bullet.draw(surface);
  }
}

bool Enemy::isOffScreen() const {
  return rect.x + rect.w < 0 || rect.x > W ||
         rect.y + rect.h < 0 || rect.y > H;
}

bool Enemy::checkBulletCollision(const std::vector<Bullet>& playerBullets) {
  for (const Bullet& bullet : playerBullets) {
    int bulletX = bullet.getX();
    int bulletY = bullet.getY();
    int bulletRadius = bullet.getWidth() / 2;

    if (bulletX + bulletRadius > rect.x &&
        bulletX - bulletRadius < rect.x + rect.w &&
        bulletY + bulletRadius > rect.y &&
        bulletY - bulletRadius < rect.y + rect.h) {
      return true;
    }
  }
  return false;
}

void Enemy::takeDamage() {
  if (spawnIFrame <= 0.0f) return;
  health--;
  if (health <= 0) {
    //
  }
}
