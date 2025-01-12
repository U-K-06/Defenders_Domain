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

  void setPosition(int x,int y);

  bool isEnemeyInRange(const Enemy &enemy) const;

  void setPlacementTime(time_t time);
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
                       std::vector<Enemy>::iterator &it);


  void poison_explode(std::vector<Enemy> &enemies,
                       int range,
                       int GRID_SIZE,
                       std::vector<Enemy>::iterator &it,
                       std::string &poison_color);

  void ice_explode(std::vector<Enemy> &enemies,
                    int range,
                    std::vector<Enemy>::iterator &it);

  void wind_explode(std::vector<Enemy> &enemies,
                     int range,
                     std::vector<Enemy>::iterator &it,
                     int door_x,
                     int door_y);
                     
  void water_explode(std::vector<Enemy>& enemies,
                      int range, 
                      std::vector<Enemy>::iterator& it,
                      int door_x,
                      int door_y);


  void shadow_explode(std::vector<Enemy> &enemies,
                    int number_of_bombs,
                    int door_x,
                    int door_y,
                    int GRID_SIZE,
                    std::string poison_color,
                    std::vector<Enemy>::iterator &it,
                    std::vector<BombPositionDataClass> &bombs);

  void explode(std::vector<Enemy> &enemies,
                int range,
                int door_x,
                int door_y,
                int GRID_SIZE,
                std::string poison_color,
                int number_of_bombs,
                std::vector<BombPositionDataClass> bombs,
                int &score);

  bool operator==(const BombPositionDataClass &other) const {
     return index == other.index && x == other.x && y == other.y; 
  }

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
  std::pair<int, int> findNearestPortalCorner(const std::vector<std::pair<int, int>>& portal_corners,
                                               int x,
                                               int y);
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
                           BombPositionData &bombPosition);
};

#endif
