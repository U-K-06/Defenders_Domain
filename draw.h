#pragma once

#include "Game.h"

class Draw {
public:
  void grid(int GRID_SIZE, std::string tower_names[], int active_tower, int selection_tower, int active_grid_x, int active_grid_y, bool is_place_mode_active, TowerPositionData TowerPosition);
private:
  std::string place_tower(int index);
  bool check_tower_position(int x, int y, TowerPositionData& TowerPosition);
  int get_tower_index(int x, int y, TowerPositionData& TowerPosition);
  void top_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, TowerPositionData TowerPosition);
  void render_tower_names(int& name_index, int selection_tower, int active_tower, bool is_place_mode_active, std::string tower_names[]);
  void bottom_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, TowerPositionData TowerPosition);
};

