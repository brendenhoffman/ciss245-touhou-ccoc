// Brenden Hoffman
// p01
// Player.cpp
#include <typeinfo>
#include "Player.h"
#include "Bullet.h"
#include "Constants.h"
#include "Enemy.h"
#include "Includes.h"
#include "Upgrade.h"

Player::Player(int x, int y, const char* imagePath, int initialLives)
  : sprite(imagePath), rect(sprite.getRect()), speed(4), lastShotTime(0),
    fireRate(0.2f), health(3), lives(initialLives)
{
  rect.x = x;
  rect.y = y;
  hasTriple = false;
  triplePower = 0;
}

void Player::update(const KeyPressed& keys) {
  int moveSpeed = (keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT]) ? speed / 2 : speed;

  if (keys[LEFTARROW])  rect.x -= moveSpeed;
  if (keys[RIGHTARROW]) rect.x += moveSpeed;
  if (keys[UPARROW])    rect.y -= moveSpeed;
  if (keys[DOWNARROW])  rect.y += moveSpeed;

  if (rect.x < 0) rect.x = 0;
  if (rect.y < 0) rect.y = 0;
  if (rect.x + rect.w > W) rect.x = W - rect.w;
  if (rect.y + rect.h > H) rect.y = H - rect.h;

  float currentTime = SDL_GetTicks() / 1000.0f;

  if (keys[SPACE] && (currentTime - lastShotTime >= fireRate)) {
    shoot(BLUE_BULLET);
    lastShotTime = currentTime;
  }

  for (Bullet& bullet : bullets) {
    bullet.update();
  }
}

void Player::shoot(BulletColor color) {
  int bulletX = rect.x + rect.w;
  int bulletY = rect.y + rect.h / 2;
  float speed = 5;
  float angle = 0;

  if (hasTriple) {
    int radius = (triplePower == 2) ? 6 : 5;
    int spread = (triplePower == 2) ? 12 : 10;

    for (int i = -1; i <= 1; ++i) {
      bullets.push_back(Bullet(
        bulletX, bulletY + i * spread, radius, speed, angle, color));
    }
  } else {
    bullets.push_back(Bullet(bulletX, bulletY, 5, speed, angle, color));
  }
}

void Player::draw(Surface* surface, const KeyPressed& keys) {
  surface->put_image(sprite, rect);

  if (keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT]) {
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    int radius = 5;
    surface->put_circle(cx, cy, radius, BLUE);
  }

  for (const Bullet& bullet : bullets) {
    bullet.draw(*surface);
  }
}

bool Player::checkCollision(GameObject& obj, bool isFocusing) {
  if (isFocusing) {
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    int radius = 3;

    int closestX = std::max(obj.getX(), std::min(cx, obj.getX() + obj.getWidth()));
    int closestY = std::max(obj.getY(), std::min(cy, obj.getY() + obj.getHeight()));

    int dx = cx - closestX;
    int dy = cy - closestY;

    return dx * dx + dy * dy <= radius * radius;
  } else {
    return rect.x + rect.w > obj.getX() &&
           rect.x < obj.getX() + obj.getWidth() &&
           rect.y + rect.h > obj.getY() &&
           rect.y < obj.getY() + obj.getHeight();
  }
}

void Player::reset() {
  rect.x = 30;
  rect.y = H / 2;
  health = 3;
}

void Player::takeDamage() {
  health--;
  if (health <= 0) {
    lives--;
    if (lives > 0) {
      reset();
    } else {
      //
    }
  } else {
    //
  }
}

void Player::applyUpgrade(UpgradeType type) {
  switch (type) {
    case UPG_FIRERATE:
      fireRate *= 0.8f;
      break;
    case UPG_LIFE:
      lives++;
      break;
    case UPG_TRIPLE:
      if (!hasTriple) {
        hasTriple = true;
        triplePower = 1;
      } else if (triplePower < 2) {
        triplePower = 2;
      }
      break;
  }
}
