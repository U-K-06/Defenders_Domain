#pragma once

#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <vector>

struct Enemy {
  int type;
  std::string color;
  int x;
  int y;
};

struct TowerPositionDataStruct {
  int index;
  int x;
  int y;
  int level = 0;
  time_t last_upgrade_time = 0;
};

using TowerPositionData = std::vector<TowerPositionDataStruct>;

class Game {
public:
  int Run();
  void toggle_state(bool& is_place_mode_active);
  void Move(bool is_place_mode_active, std::string direction, int& active_grid_y, int &active_grid_x, int &selection_tower, int number_of_towers, int GRID_SIZE);
  void hide_cursor();
  void clear_screen(int GRID_SIZE);
  std::tuple<int, int> calculate_grid();
  void calculate_tower_positions(int GRID_SIZE, int active_tower, int active_grid_x, int active_grid_y, TowerPositionData& TowerPosition);
  void display_tower_positions(const TowerPositionData& TowerPosition);

private:
  std::vector<TowerPositionDataStruct> placed_towers_list;
  std::vector<Enemy> enemies;
  int enemy_type();
  std::string enemy_color(int choice);
  void play_background_music();
};

#endif
