#pragma once

#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <vector>
#include <chrono>
#include <cmath>
#include <vector>

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

private:
  int index;
  int x, y;
};

class TowerPositionDataClass
{
public:
  TowerPositionDataClass(int idx, int posX, int posY, Tower tower)
      : index(idx), x(posX), y(posY), tower(tower) {}

  int getIndex() const { return index; }
  int getX() const { return x; }
  int getY() const { return y; }

  
  void explode(std::vector<Enemy> &enemies,std::vector<TowerPositionDataClass> towers)
  {
    int indexTower = -1;
    for (auto it = enemies.begin(); it != enemies.end();)
    {
      if (tower.isEnemeyInRange(*it))
      {
        // std::cout << "Enemy destroyed at position: (" << it->x << ", " << it->y << ")\n";
        it = enemies.erase(it);
      }
      else
      {
        ++it;
      }
    }
    for(int i = 0;i<towers.size();i++){
      if(towers[i] == (*this)){

         indexTower = i;
         break;
      }
    }

    if(indexTower != -1){
      std::cout << "TEST PASSED!" << std::endl;
      towers.erase(towers.begin() + indexTower);
    }
  }

  void ElectricBomb(std::vector<Enemy> &enemies,std::vector<TowerPositionDataClass> towers)
  {
    this->explode(enemies,towers);
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
  bool sleep(int milliseconds);
};

#endif
