// Brenden Hoffman
// p01
// WaveManager.cpp
#include <cmath>
#include "WaveManager.h"
#include "Constants.h"
#include "ZigZagEnemy.h"
#include "PhaserEnemy.h"
#include "Bomber.h"
#include "BossEnemy.h"

void WaveManager::update(float deltaTime, std::vector<Enemy*>& enemies) {
  if (!active && enemies.empty()) {
    resetDelay += deltaTime;
    if (resetDelay >= 2.0f) {
      resetDelay = 0.0f;
      if (bossWaveActive) {
        bossWaveActive = false;
        waveCount = 0;
        loopCount++;
      }
      startNextWave();
    }
  }

  timer += deltaTime;

  while (nextSpawnIndex < currentWave.size() &&
         timer >= currentWave[nextSpawnIndex].spawnTime) {
    enemies.push_back(currentWave[nextSpawnIndex].createFunc());
    nextSpawnIndex++;
  }

  if (nextSpawnIndex >= currentWave.size()) {
    active = false;
  }
}

void WaveManager::startNextWave() {
  timer = 0;
  nextSpawnIndex = 0;
  active = true;
  currentWave.clear();

  waveCount++;

  if (waveCount == 1) {

    // Wave 1
    // 1 Bomber close to the front and a group of ZigZags
    currentWave.push_back({ 0.0f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H / 3);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 0.1f, [this]() -> Enemy* {
      Bomber* e = new Bomber();
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 0.4f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H / 3);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 0.8f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H / 3);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});
  }

  else if (waveCount == 2) {

    // Wave 2
    // A phaser and several Bombers over time
    currentWave.push_back({ 0.0f, [this]() -> Enemy* {
      PhaserEnemy* e = new PhaserEnemy(H / 3);
      e->setHealth(7 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 0.0f, [this]() -> Enemy* {
      Bomber* e = new Bomber();
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 4.0f, [this]() -> Enemy* {
      Bomber* e = new Bomber();
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 8.0f, [this]() -> Enemy* {
      Bomber* e = new Bomber();
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});
  }

  else if (waveCount == 4) {

    // Wave 4
    // one Phaser after another, Bomber shows up behind them
    currentWave.push_back({ 0.0f, [this]() -> Enemy* {
      PhaserEnemy* e = new PhaserEnemy(H - H / 3);
      e->setHealth(7 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 3.0f, [this]() -> Enemy* {
      PhaserEnemy* e = new PhaserEnemy(H / 2);
      e->setHealth(7 * std::pow(2, loopCount));
      return e;
    }});

    currentWave.push_back({ 8.0f, [this]() -> Enemy* {
      Bomber* e = new Bomber();
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }});
  }

  else if (waveCount == 6) {

    // Boss wave
    bossWaveActive = true;
    currentWave.push_back({ 0.1f, [this]() -> Enemy* {
      BossEnemy* e = new BossEnemy();
      e->setHealth(50 * std::pow(2, loopCount));
      return e;
    }});
  }

  else {

    // Filler wave
    // Waves 3 and 5
    // Two groups of ZigZags
    currentWave.push_back({ 0.0f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H / 4);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }}); // Group 1

    currentWave.push_back({ 0.0f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H - H / 4);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }}); // Group 2

    currentWave.push_back({ 0.4f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H / 4);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }}); // Group 1

    currentWave.push_back({ 0.4f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H - H / 4);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }}); // Group 2

    currentWave.push_back({ 0.8f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H / 4);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }}); // Group 1

    currentWave.push_back({ 0.8f, [this]() -> Enemy* {
      ZigZagEnemy* e = new ZigZagEnemy(H - H / 4);
      e->setHealth(3 * std::pow(2, loopCount));
      return e;
    }}); // Group 2
  }
}

