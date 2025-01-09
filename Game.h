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

  void normal_explode(std::vector<Enemy> &enemies,
                       int range,
                       std::vector<Enemy>::iterator &it)
  {
    // std::cout << "Enemy destroyed at position: (" << it->x << ", " << it->y << ")\n";
    it = enemies.erase(it);
  }

  void poison_explode(std::vector<Enemy> &enemies,
                       int range,
                       int GRID_SIZE,
                       std::vector<Enemy>::iterator &it,
                       std::string &poison_color)
  {
    normal_explode(enemies, range, it);

    int center_x = it->x, center_y = it->y;

    for (int dx = -range; dx <= range; ++dx)
    {
      for (int dy = -range; dy <= range; ++dy)
      {
        int new_x = center_x + dx;
        int new_y = center_y + dy;

        if (new_x >= 0 && new_x < GRID_SIZE && new_y >= 0 && new_y < GRID_SIZE)
        {
          
        }
      }
    }
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
                    int number_of_bombs,
                    int door_x,
                    int door_y,
                    int GRID_SIZE,
                    std::string poison_color,
                    std::vector<Enemy>::iterator &it,
                    std::vector<BombPositionDataClass> &bombs)
  {
    int bomb_type = rand() % (number_of_bombs - 1);
    switch(bomb_type)
    {
      case 2:
        poison_explode(enemies, 1, GRID_SIZE, it, poison_color);
        break;
      case 3:
        water_explode(enemies, 1, it, 0, 0);
        break;
      case 4:
        ice_explode(enemies, 1, it);
        break;
      case 5:
        wind_explode(enemies, 1, it, 0, 0);
        break;
      default:
        normal_explode(enemies, 1, it);
        break;
    } 
  }

  void explode(std::vector<Enemy> &enemies,
                int range,
                int door_x,
                int door_y,
                int GRID_SIZE,
                std::string poison_color,
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
          poison_explode(enemies, range, GRID_SIZE, it, poison_color);
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
          shadow_explode(enemies, number_of_bombs, door_x, door_y, GRID_SIZE, poison_color, it, bombs);
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

  void simulateKeyPress(WORD virtualKey, bool ctrl = false);
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
  int random_bomb_spawner(int number_of_bombs);

private:
  std::vector<BombPositionDataClass> placed_bombs_list;
  std::vector<Enemy> enemies;
  int enemy_type();
  std::string enemy_color(int choice);
  bool isBombPlacedAt(int x, int y) const;
  bool isEnemyInPortalCorners(const std::vector<std::pair<int, int>> &portal_corners,
                               int enemy_x,
                               int enemy_y);
  void spawn_shadow_entity(int GRID_SIZE, 
                           int active_bomb,
                           int &dx,
                           int &dy,
                           BombPositionData &bombPosition)
  {
    const int max_attempts = 10;
    int attempts = 0;
    while (attempts < max_attempts) {
      int random = rand() % 4;
      int sign_x = rand() % 2 ? 1 : -1;
      int sign_y = rand() % 2 ? 1 : -1;

      int new_dx = dx;
      int new_dy = dy;

      switch (random) {
          case 0:
              new_dx -= sign_x; // don't let them be new_dx, new_dy -ve or > GRID_SIZE
              new_dy += sign_y;
              std::cout << new_dx << " " << new_dy << std::endl;
              attempts++;
              break;
          case 1:
              new_dx -= sign_x;
              new_dy -= sign_y;
              std::cout << new_dx << " " << new_dy << std::endl;
              attempts++;
              break;
          case 2:
              new_dy += sign_x;
              new_dx += sign_y;
              std::cout << new_dx << " " << new_dy << std::endl;
              attempts++;
              break;
          case 3:
              new_dx += sign_x;
              new_dy -= sign_y;
              std::cout << new_dx << " " << new_dy << std::endl;
              attempts++;
              break;
      }
      if (!isBombPlacedAt(new_dx, new_dy)) {
          dx = new_dx;
          dy = new_dy;
          calculate_bomb_positions(GRID_SIZE,
                                    active_bomb,
                                    dx,
                                    dy,
                                    bombPosition);
          break;
      }
    }
  }
};

#endif
