#ifndef GAME_HPP
#define GAME_HPP

#include <eadk.h>
#include <stdint.h>

namespace BrawlNW {

constexpr int SCREEN_W = 320;
constexpr int SCREEN_H = 240;
constexpr int ARENA_W = 640;
constexpr int ARENA_H = 480;
constexpr int MAX_BULLETS = 24;
constexpr int MAX_ENEMIES = 6;
constexpr int MAX_WALLS = 14;

struct Rect {
  int x;
  int y;
  int w;
  int h;
};

struct Bullet {
  bool active;
  bool fromPlayer;
  float x;
  float y;
  float vx;
  float vy;
  int life;
};

struct Enemy {
  bool alive;
  float x;
  float y;
  int hp;
  int maxHp;
  int cooldown;
  int moveTimer;
  float vx;
  float vy;
};

class Game {
public:
  void run();

private:
  void initLevel();
  void update(eadk_keyboard_state_t keys);
  void render();
  void spawnBullet(bool fromPlayer, float x, float y, float dirX, float dirY, float speed);
  bool collidesWall(float x, float y, int radius) const;

  float m_px;
  float m_py;
  int m_hp;
  int m_maxHp;
  int m_ammo;
  int m_reloadTimer;
  int m_shootCooldown;
  float m_aimX;
  float m_aimY;
  int m_score;
  bool m_gameOver;

  Bullet m_bullets[MAX_BULLETS];
  Enemy m_enemies[MAX_ENEMIES];
  Rect m_walls[MAX_WALLS];
};

} // namespace BrawlNW

#endif
