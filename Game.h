#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>

struct TowerPositionDataStruct {
  int index;
  int x;
  int y;
};

using TowerPositionData = std::vector<TowerPositionDataStruct>;

class Game {
public:
    int Run();
    void toggle_state(bool& is_place_mode_active);
    void Move(bool is_place_mode_active, std::string direction, int& active_grid_y, int &active_grid_x, int &selection_tower, int number_of_towers, int GRID_SIZE);
    void hide_cursor();
    void clear_screen(int GRID_SIZE);
    int calculate_grid();
    void calculate_tower_positions(int GRID_SIZE, int active_tower, int active_grid_x, int active_grid_y, TowerPositionData& TowerPosition);
    void display_tower_positions(const TowerPositionData& TowerPosition);

private:
  std::vector<TowerPositionDataStruct> placed_towers_list;
};

#endif
