// Brenden Hoffman
// p01
// main.cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>

#include "Color.h"
#include "Image.h"
#include "Includes.h"
#include "Constants.h"
#include "Rect.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Player.h"
#include "Bullet.h"
#include "WaveManager.h"
#include "Upgrade.h"
#include "UpgradeType.h"

enum GameState {
  STATE_TITLE,
  STATE_PLAYING,
  STATE_GAMEOVER,
  STATE_CREDITS
};

struct Star {
  float x, y;
  int radius;
  float speed;
};

struct Explosion {
  float x, y;
  float timer = 0.0f;
  float duration = 1.0f;
};

int main() {
  Surface surface(W, H);
  Event event;
  Player player(30, H / 2, "images/Marisa.gif");
  std::vector<Enemy*> enemies;
  std::vector<Enemy*> deadEnemies;
  std::vector<Upgrade> upgrades;
  std::vector<Star> stars;
  std::vector<Explosion> explosions;
  WaveManager waveManager;
  int score = 0;
  float creditTimer = 0.0f;
  float creditDelay = 0.0f;
  float deltaTime = 1.0f / 60.0f;
  Sound explosion("sounds/explosion.wav");
  Sound music("sounds/Halo.ogg");
  Font font("fonts/FreeSans.ttf", 36);
  Font fontSmall("fonts/FreeSans.ttf", 20);
  Image logo("images/touhou.gif");
  Color starColor = { 200, 200, 200, 0 };
  int starCount = 100;

  for (int i = 0; i < starCount; ++i) {
    int radius = (rand() % 3) + 1;
    float speed = (radius == 1) ? 1.5f : (radius == 2) ? 0.8f : 0.4f;

    stars.push_back({
    static_cast<float>(rand() % W),
    static_cast<float>(rand() % H),
    radius,
    speed
    });
  }

  GameState gameState = STATE_TITLE;
  bool running = true;

  while (running) {
    if (event.poll() && event.type() == QUIT) break;
    KeyPressed keypressed = get_keypressed();

    switch (gameState) {
      case STATE_TITLE: {
        if (keypressed[SDLK_RETURN]) {
          gameState = STATE_PLAYING;
        }

        surface.lock();
        surface.fill(BLACK);

        Rect logoRec = logo.getRect();
        logoRec.x = W / 2 - logoRec.w / 2;
        logoRec.y = H / 3;
        surface.put_image(logo, logoRec);

        Image titleText(fontSmall.render("Press Enter to Start", WHITE));
        Rect title = titleText.getRect();
        title.x = W / 2 - title.w / 2;
        title.y = H - H / 4;
        surface.put_image(titleText, title);

        Image nameText(fontSmall.render("Brenden Hoffman", WHITE));
        Rect name = nameText.getRect();
        name.x = name.w / 2;
        name.y = H - name.h - 10;
        surface.put_image(nameText, name);

        surface.unlock();
        surface.flip();
        delay(16);
        continue;
      }

      case STATE_GAMEOVER: {
        if (keypressed[SDLK_RETURN]) {
          gameState = STATE_CREDITS;
          creditTimer = 0.0f;
          creditDelay = 0.3f;
          continue;
        }

        surface.lock();
        surface.fill(BLACK);

        Image gameOverText(font.render("Game Over", WHITE));
        Rect over = gameOverText.getRect();
        over.x = W / 2 - over.w / 2;
        over.y = H / 2 - 20;
        surface.put_image(gameOverText, over);

        Image exitPrompt(fontSmall.render("Press Enter to Exit", WHITE));
        Rect exit = exitPrompt.getRect();
        exit.x = W / 2 - exit.w / 2;
        exit.y = H / 2 + 20;
        surface.put_image(exitPrompt, exit);

        std::string scoreStr = "Score: " + std::to_string(score);
        Image scoreText(font.render(scoreStr.c_str(), YELLOW));
        Rect score = scoreText.getRect();
        score.x = W / 2 - score.w / 2;
        score.y = 150;
        surface.put_image(scoreText, score);

        surface.unlock();
        surface.flip();
        delay(16);
        continue;
      }

      case STATE_CREDITS: {
        creditTimer += deltaTime;
        if (creditDelay > 0.0f) {
          creditDelay -= deltaTime;
        }
        if ((creditDelay <= 0.0f && keypressed[SDLK_RETURN])
            || creditTimer >= 10.0f) {
          running = false;
          continue;
        }

        surface.lock();
        surface.fill(BLACK);

        Image thanksText(font.render("Thanks for playing!", WHITE));
        Rect thanks = thanksText.getRect();
        thanks.x = W / 2 - thanks.w / 2;
        thanks.y = 40;
        surface.put_image(thanksText, thanks);

        Image songCred(font.render("Music: Halo Theme - Bungie", WHITE));
        Rect song = songCred.getRect();
        song.x = W / 2 - song.w / 2;
        song.y = H / 4;
        surface.put_image(songCred, song);

        Image remixCred(font.render( "Cover: Unpragmatic Covers", WHITE));
        Rect remix = remixCred.getRect();
        remix.x = W / 2 - remix.w / 2;
        remix.y = song.y + 40;
        surface.put_image(remixCred, remix);

        Image gameCred(font.render( "Original Games by ZUN", WHITE));
        Rect game = gameCred.getRect();
        game.x = W / 2 - game.w / 2;
        game.y = remix.y + 60;
        surface.put_image(gameCred, game);

        Image liowCred(font.render( "Thank you Dr. Liow", WHITE));
        Rect liow = liowCred.getRect();
        liow.x = W / 2 - liow.w / 2;
        liow.y = game.y + 50;
        surface.put_image(liowCred, liow);

        Image prompt(fontSmall.render("Press Enter to Skip", WHITE));
        Rect skip = prompt.getRect();
        skip.x = W / 2 - skip.w / 2;
        skip.y = H - skip.h - 10;
        surface.put_image(prompt, skip);

        surface.unlock();
        surface.flip();
        delay(16);
        continue;
      }

      case STATE_PLAYING:
        break;
    }

    // Main game loop
    music.play();

    player.update(keypressed);
    for (Enemy* enemy : enemies) {
      enemy->update(deltaTime);
    }

    std::vector<Bullet>& bullets = const_cast<std::vector<Bullet>&>(
      player.getBullets()
    );
    for (Enemy* enemy : enemies) {
      std::vector<Bullet>::iterator it = bullets.begin();
      while (it != bullets.end()) {
        if (enemy->checkBulletCollision({ *it })) {
          enemy->takeDamage();
          score += 100;
          if (enemy->getHealth() <= 0) {
            score += 500;
            explosion.play();
            float ex = enemy->getX() + enemy->getWidth() / 2;
            float ey = enemy->getY() + enemy->getHeight() / 2;
            explosions.push_back({ ex, ey });
          }
          it = bullets.erase(it);
          break;
        } else {
          ++it;
        }
      }
    }

    waveManager.update(deltaTime, enemies);

    enemies.erase(
      std::remove_if(enemies.begin(), enemies.end(),
        [&deadEnemies, &upgrades](Enemy* enemy) {
            if (enemy->getHealth() <= 0) {
              // 25% chance to drop
              if (rand() % 4 == 0) {
                UpgradeType type = static_cast<UpgradeType>(rand() % 3);
                upgrades.push_back(Upgrade(enemy->getX(), enemy->getY(), type));
              }
              deadEnemies.push_back(enemy);
              return true;
            }
          return false;
        }
      ),
    enemies.end());

    bool isFocusing = keypressed[SDLK_LSHIFT] || keypressed[SDLK_RSHIFT];
    for (Enemy* enemy : enemies) {
      std::vector<Bullet>& bullets = enemy->getBullets();
      std::vector<Bullet>::iterator it = bullets.begin();
      while (it != bullets.end()) {
        it->update();
        if (player.checkCollision(*it, isFocusing)) {
          player.takeDamage();
          score -= 300;
          it = bullets.erase(it);
          break;
        } else {
          ++it;
        }
      }
    }

    for (Enemy* enemy : deadEnemies) {
      std::vector<Bullet>& bullets = enemy->getBullets();
      std::vector<Bullet>::iterator it = bullets.begin();
      while (it != bullets.end()) {
        it->update();
        if (player.checkCollision(*it, isFocusing)) {
          player.takeDamage();
          it = bullets.erase(it);
          break;
        } else {
          ++it;
        }
      }
    }

    for (Enemy* enemy : enemies) {
      if (player.checkCollision(*enemy, isFocusing)) {
        player.takeDamage();
        break;
      }
    }

    if (player.getLives() <= 0) {
      gameState = STATE_GAMEOVER;
      continue;
    }

    enemies.erase(
      std::remove_if(enemies.begin(), enemies.end(),
        [](Enemy* enemy) {
          if (enemy->shouldDespawn()) {
            delete enemy;
            return true;
          }
          return false;
        }),
      enemies.end());

    for (std::vector<Upgrade>::iterator it = upgrades.begin();
      it != upgrades.end();
    ) {
      it->update();
      if (player.checkCollision(*it, false)) {
        player.applyUpgrade(it->getType());
        it = upgrades.erase(it);
      } else if (it->isOffScreen()) {
        it = upgrades.erase(it);
      } else {
        ++it;
      }
    }

    for (const Bullet& bullet : player.getBullets()) {
      bullet.draw(surface);
    }


    surface.lock();
    surface.fill(BLACK);

    for (Star& star : stars) {
      star.x -= star.speed;

      if (star.x + star.radius < 0) {
        star.x = W;
        star.y = static_cast<float>(rand() % H);
        star.radius = (rand() % 3) + 1;
        star.speed = (star.radius == 1) ? 1.5f :
          (star.radius == 2) ? 0.8f : 0.4f;
      }

      surface.put_circle(static_cast<int>(star.x), static_cast<int>(star.y),
        star.radius, starColor);
    }

    for (std::vector<Explosion>::iterator it = explosions.begin();
      it != explosions.end();
    ) {
      it->timer += deltaTime;

      float progress = it->timer / it->duration;
      if (progress >= 1.0f) {
        it = explosions.erase(it);
        continue;
      }

      int radius = static_cast<int>(progress * 30);
      surface.put_circle(static_cast<int>(it->x), static_cast<int>(it->y),
        radius, YELLOW);
      ++it;
    }

    player.draw(&surface, keypressed);
    for (Enemy* enemy : enemies) {
      enemy->draw(surface);
    }
    for (Enemy* enemy : deadEnemies) {
      std::vector<Bullet>& bullets = enemy->getBullets();
      for (const Bullet& bullet : bullets) {
        bullet.draw(surface);
      }
    }
    for (const Upgrade& upgrade : upgrades) {
      upgrade.draw(surface);
    }

    // UI
    // Score (top left)
    {
      std::string scoreStr = "Score: " + std::to_string(score);
      Image scoreImg(fontSmall.render(scoreStr.c_str(), YELLOW));
      Rect r = scoreImg.getRect();
      r.x = 10;
      r.y = 10;
      surface.put_image(scoreImg, r);
    }

    // Fleet count (bottom left)
    {
      std::string fleetStr = "Fleets: " +
        std::to_string(waveManager.getLoopCount());
      Image fleetImg(fontSmall.render(fleetStr.c_str(), WHITE));
      Rect r = fleetImg.getRect();
      r.x = 10;
      r.y = H - r.h - 10;
      surface.put_image(fleetImg, r);
    }

    // Health (green *) (bottom center)
    {
      std::string healthStr = "Health: ";
      for (int i = 0; i < player.getHealth(); ++i) {
        healthStr += "* ";
      }
      Image healthImg(fontSmall.render(healthStr.c_str(), GREEN));
      Rect hr = healthImg.getRect();
      hr.x = W / 2 - hr.w / 2;
      hr.y = H - hr.h - 10;
      surface.put_image(healthImg, hr);

      //Lives (bottom right)
      std::string livesStr = "Lives: " + std::to_string(player.getLives());
      Image livesImg(fontSmall.render(livesStr.c_str(), WHITE));
      Rect lr = livesImg.getRect();
      lr.x = W - lr.w - 10;
      lr.y = H - lr.h - 10;
      surface.put_image(livesImg, lr);
    }

    surface.unlock();
    surface.flip();

    delay(16); // ~60 FPS
  }

  for (Enemy* enemy : enemies) {
    delete enemy;
  }
  for (Enemy* enemy : deadEnemies) {
    delete enemy;
  }

  return 0;
}
