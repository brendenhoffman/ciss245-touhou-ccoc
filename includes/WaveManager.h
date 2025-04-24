// Brenden Hoffman
// p01
// WaveManager.h
#pragma once
#include <vector>
#include <functional>
#include "Enemy.h"

struct SpawnEvent {
  float spawnTime;
  std::function<Enemy*()> createFunc;
};

class WaveManager {
public:
  void update(float deltaTime, std::vector<Enemy*>& enemies);
  bool isWaveActive() const { return active; }
  int getLoopCount() const { return loopCount; }

private:
  bool active = false;
  float timer = 0;
  std::vector<SpawnEvent> currentWave;
  size_t nextSpawnIndex = 0;
  bool bossWaveActive = false;
  int waveCount = 0;
  float resetDelay = 0.0f;
  int loopCount = 0;

  void startNextWave();
};

