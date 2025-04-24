// Brenden Hoffman
// p01
// Player.h
#pragma once
#include "Bullet.h"
#include "Includes.h"
#include <vector>
#include "Upgrade.h"
#include "UpgradeType.h"

class Player {
public:
  Player(int x, int y, const char* imagePath, int initialLives = 3);
  void update(const KeyPressed& keys);
  void shoot(BulletColor color);
  void draw(Surface* surface, const KeyPressed& keys);
  bool checkCollision(GameObject& obj, bool isFocusing);
  void takeDamage();
  int getHealth() const { return health; }
  int getLives() const { return lives; }
  void reset();
  void applyUpgrade(UpgradeType type);
  float getFireRate() const { return fireRate; }
  bool hasTripleShot() const { return hasTriple; }
  int getTriplePower() const { return triplePower; }
  const std::vector<Bullet>& getBullets() const { return bullets; }

private:
  Image sprite;
  Rect rect;
  int speed;
  std::vector<Bullet> bullets;
  float lastShotTime;
  float fireRate;
  int health;
  int lives;
  bool hasTriple;
  int triplePower;
};
