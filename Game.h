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
  int MOVEMENT_SPEED = 5.0f;

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

  int random_bomb_spawner(int number_of_bombs)
    {
      int random_bomb = 1 + rand() % 100;
      if (random_bomb >= 1 && random_bomb <= 5)         return 6;
      else if (random_bomb >= 6 && random_bomb <= 15)   return 5;
      else if (random_bomb >= 16 && random_bomb <= 30)  return 4;
      else if (random_bomb >= 31 && random_bomb <= 56)  return 3;
      else if (random_bomb >= 57 && random_bomb <= 81)  return 2;
      else if (random_bomb >= 82 && random_bomb <= 100) return 1;
      else return -1;
    }

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

    it->MOVEMENT_SPEED -= 2.5f;

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

    if (abs(dx) > abs(dy))  (dx > 0) ? (it->x + 1 >= range)
                                      ? it = enemies.erase(it)
                                      : (it->x += 1, ++it)
                                     : (it->x - 1 < 0)
                                      ? it = enemies.erase(it)
                                      : (it->x -= 1, ++it);
    else  (dy > 0) ? (it->y + 1 >= range)
                    ? it = enemies.erase(it)
                    : (it->y += 1, ++it)
                   : (it->y - 1 < 0)
                    ? it = enemies.erase(it)
                    : (it->y -= 1, ++it);
  }
  void water_explode(std::vector<Enemy>& enemies,int range ,std::vector<Enemy>::iterator& it,int door_x,int door_y)
  {
    it -> MOVEMENT_SPEED += (2 + rand() % 3) + 0.3;
    wind_explode(enemies,range,it,door_x,door_y);
  }

  void shadow_explode(std::vector<Enemy> &enemies,
                    int range,
                    int number_of_bombs,
                    std::vector<Enemy>::iterator &it,
                    std::vector<BombPositionDataClass> &bombs)
  {
     
    int bomb_x = getX();
    int bomb_y = getY();

    // int dx = (rand() % (2 * range + 1)) - range;
    // int dy = (rand() % (2 * range + 1)) - range;

    int dx = bomb_x + 1;
    int dy = bomb_y + 1;

    while (abs(dx) != abs(dy) || dx == 0 || dy == 0) {
        dx = (rand() % (2 * range + 1)) - range;
        dy = (rand() % (2 * range + 1)) - range;
    }

    int random_bomb = random_bomb_spawner(number_of_bombs);
    Bomb new_bomb(random_bomb);
    BombPositionDataClass new_bomb_positions(random_bomb, dx, dy, new_bomb,time(nullptr));
    bombs.push_back(new_bomb_positions);
  }

  void explode(std::vector<Enemy> &enemies,
                int range,
                int door_x,
                int door_y,
                int number_of_bombs,
                std::vector<BombPositionDataClass> bombs)
  {
    for (auto it = enemies.begin(); it != enemies.end();)
    {
      int distance = my_max(std::abs(it->x - x), std::abs(it->y - y));
      
      if (distance <= range)
      {
        switch (getIndex())
        {
        case 2:
          poison_explode(enemies, range, it);
          break;
        case 3:
          water_explode(enemies, range, it,door_x,door_y);
          break;
        case 4:
          ice_explode(enemies, range, it);
          break;
        case 5:
          wind_explode(enemies, range, it, door_x, door_y);
          break;
        case 6:
          shadow_explode(enemies, range, number_of_bombs, it, bombs);
          break;
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

  float calculateDistance(int x1, int y1, int x2, int y2);
  std::pair<int, int> findNearestPortalCorner(const std::vector<std::pair<int, int>>& portal_corners, int x, int y);
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
  bool isEnemyInPortalCorners(const std::vector<std::pair<int, int>> &portal_corners,
                               int enemy_x,
                               int enemy_y);
};

#endif
