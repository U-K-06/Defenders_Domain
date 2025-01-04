#pragma once

#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <vector>
#include <chrono>
#include <cmath>

#define my_max(a, b) (((a) > (b)) ? (a) : (b))


class Enemy
{
public:
  int type;
  int health;
  std::string color;
  int x;
  int y;
  int hasMoved = false;
  int is_slowed = false;
  int is_poisoned = false;

  std::chrono::steady_clock::time_point last_move_time = std::chrono::steady_clock::now();
  Enemy() : type(0), health(type), color("default"), x(x), y(y) {}

  Enemy(int initialHealth, int enemyType)
      : type(enemyType), health(enemyType), color("default"), x(0), y(0) {}
};

class Bomb
{
public:
  Bomb(int index)
      : index(index) {}

  void setPosition(int x,
                    int y)
  {
    this->x = x;
    this->y = y;
  }

  bool isEnemeyInRange(const Enemy &enemy) const
  {
    int range = 5 - index;
    int distance = static_cast<int>(std::hypot(enemy.x - x, enemy.y - y));
    return distance <= range;
  }

  void setPlacementTime(time_t time) { placement_time = time; }

private:
  int index;
  int x, y;
  time_t placement_time;
};

class BombPositionDataClass
{
public:
  time_t placement_time;

  BombPositionDataClass(int idx, int posX, int posY, Bomb tower, time_t time)
      : index(idx), x(posX), y(posY), tower(tower), placement_time(time) {}

  int getIndex() const { return index; }
  int getX() const { return x; }
  int getY() const { return y; }

  void normal_explode(std::vector<Enemy> &enemies,
                       int range,
                       std::vector<Enemy>::iterator &it)
  {
    // std::cout << "Enemy destroyed at position: (" << it->x << ", " << it->y << ")\n";
    it = enemies.erase(it);
  }

  void poison_explode(std::vector<Enemy> &enemies,
                       int range,
                       std::vector<Enemy>::iterator &it)
  {
    std::string purple = "\033[38;5;93m";
  }

  void ice_explode(std::vector<Enemy> &enemies,
                    int range,
                    std::vector<Enemy>::iterator &it)
  {
    int moveAmount = rand() % 2 + 3;
    std::cout << moveAmount << std::endl;

    // TODO: Make 2.5 * the enemy's movement speed

    (rand() % 2 == 0) ? ((it->x - moveAmount < 0)
                       ? it = enemies.erase(it)
                       : (it->x -= moveAmount, ++it))
                      : ((it->y - moveAmount < 0)
                       ? it = enemies.erase(it)
                       : (it->y -= moveAmount, ++it));
  }

  void wind_explode(std::vector<Enemy> &enemies,
                     int range,
                     std::vector<Enemy>::iterator &it,
                     int door_x,
                     int door_y)
  {
    int dx = it->x - door_x;
    int dy = it->y - door_y;

    if (abs(dx) > abs(dy))  (dx > 0) ? (it->x + 2 >= range)
                                      ? it = enemies.erase(it)
                                      : (it->x += 2, ++it)
                                     : (it->x - 2 < 0)
                                      ? it = enemies.erase(it)
                                      : (it->x -= 2, ++it);
    else  (dy > 0) ? (it->y + 2 >= range)
                    ? it = enemies.erase(it)
                    : (it->y += 2, ++it)
                   : (it->y - 2 < 0)
                    ? it = enemies.erase(it)
                    : (it->y -= 2, ++it);
  }

  void explode(std::vector<Enemy> &enemies,
                int range,
                int door_x,
                int door_y)
  {
    for (auto it = enemies.begin(); it != enemies.end();)
    {
      int distance = my_max(std::abs(it->x - x), std::abs(it->y - y));
      
      if (distance <= range)
      {
        switch (getIndex()) // i changed index to getIndex()
        {
        case 2:
          poison_explode(enemies, range, it);
        case 4:
          ice_explode(enemies, range, it);
        case 5:
          wind_explode(enemies, range, it, door_x, door_y);
        default:
          normal_explode(enemies, range, it);
        }
      }
      else  ++it;
    }
  }

  bool operator==(const BombPositionDataClass &other) const { return index == other.index && x == other.x && y == other.y; }

private:
  int index;
  int x;
  int y;
  Bomb tower;
};

using BombPositionData = std::vector<BombPositionDataClass>;

class Game
{
public:
  int Run();
  void toggle_state(bool &is_place_mode_active) const;
  void Move(bool is_place_mode_active,
             std::string direction,
             int &active_grid_y,
             int &active_grid_x,
             int &selection_tower,
             int number_of_towers,
             int GRID_SIZE);
  static void hide_cursor();
  void clear_screen(int GRID_SIZE);
  std::tuple<int, int> calculate_grid();
  void calculate_bomb_positions(int GRID_SIZE,
                                 int active_tower,
                                 int active_grid_x,
                                 int active_grid_y,
                                 BombPositionData &BombPosition);
  void display_bomb_positions(const BombPositionData &BombPosition);

private:
  std::vector<BombPositionDataClass> placed_bombs_list;
  std::vector<Enemy> enemies;
  int enemy_type();
  std::string enemy_color(int choice);
};

#endif
