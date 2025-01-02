#pragma once

#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <vector>
#include <chrono>
#include <cmath>

#define max(a,b) (((a) > (b)) ? (a) : (b))

class Enemy
{
public:
  int type;
  int health;
  std::string color;
  int x;
  int y;
  int hasMoved = false;
  std::chrono::steady_clock::time_point last_move_time = std::chrono::steady_clock::now();
  Enemy() : type(0), health(type), color("default"), x(x), y(y) {}

  Enemy(int initialHealth, int enemyType)
      : type(enemyType), health(enemyType), color("default"), x(0), y(0) {}
};

class Tower
{
public:
  Tower(int index)
      : index(index) {}

  void setPosition(int x, int y)
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

class TowerPositionDataClass
{
public:
  time_t placement_time;

  TowerPositionDataClass(int idx, int posX, int posY, Tower tower, time_t time)
      : index(idx), x(posX), y(posY), tower(tower), placement_time(time) {}

  int getIndex() const { return index; }
  int getX() const { return x; }
  int getY() const { return y; }

  void explode(std::vector<Enemy> &enemies, int range)
  {
      for (auto it = enemies.begin(); it != enemies.end();)
      {
          int distance = max(std::abs(it->x - x), std::abs(it->y - y));
          if (distance <= range)
          {
              // std::cout << "Enemy destroyed at position: (" << it->x << ", " << it->y << ")\n";
              it = enemies.erase(it);
          }
          else
          {
              ++it;
          }
      }
  }

  bool operator==(const TowerPositionDataClass &other) const
  {
      return index == other.index && x == other.x && y == other.y;
  }

private:
  int index;
  int x;
  int y;
  Tower tower;
};

using TowerPositionData = std::vector<TowerPositionDataClass>;

class Game
{
public:
  int Run();
  void toggle_state(bool &is_place_mode_active) const;
  void Move(bool is_place_mode_active, std::string direction, int &active_grid_y, int &active_grid_x, int &selection_tower, int number_of_towers, int GRID_SIZE);
  static void hide_cursor();
  void clear_screen(int GRID_SIZE);
  std::tuple<int, int> calculate_grid();
  void calculate_tower_positions(int GRID_SIZE, int active_tower, int active_grid_x, int active_grid_y, TowerPositionData &TowerPosition);
  void display_tower_positions(const TowerPositionData &TowerPosition);

private:
  std::vector<TowerPositionDataClass> placed_towers_list;
  std::vector<Enemy> enemies;
  int enemy_type();
  std::string enemy_color(int choice);
};

#endif
