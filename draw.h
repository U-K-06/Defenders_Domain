#pragma once

#ifndef DRAW_H
#define DRAW_H

#include "Game.h"

class Draw {
public:
  void game_name();
  void lose_game();
  void grid(int GRID_SIZE, std::string bomb_names[], int active_bomb, int selection_bomb, int active_grid_x, int active_grid_y, bool is_place_mode_active, BombPositionData bombPosition, std::vector<Enemy>& enemies, int door_x, int door_y, int color_code, int BOMB_LEVEL[], int BOMB_RANGE[], float BOMB_TIMER[], int number_of_bombs);
  static std::string m_enemy_color;
  static int m_enemy_type;
  static bool is_bomb_placed(int x, int y, BombPositionData& bombPosition);
  bool isCompleted = false;

private:
  std::string place_bomb(int index, int bomb_lvls[]);
  int get_bomb_index(int x, int y, BombPositionData& bombPosition);
  int get_bomb_level(int x, int y, BombPositionData& bombPosition);
  void top_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, BombPositionData bombPosition, std::vector<Enemy>& enemies, int door_x, int door_y, int color_code, int BOMB_LEVEL[]);
  void render_bomb_names(int& name_index, int selection_bomb, int active_bomb, bool is_place_mode_active, std::string bomb_names[], int bomb_lvls[]);
  void bottom_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, BombPositionData bombPosition, std::vector<Enemy>& enemies, int door_x, int door_y, int color_code);
  void mid_grid(int i, int selection_bomb, int active_bomb, bool is_place_mode_active, int GRID_SIZE, int active_grid_x, int active_grid_y, int door_x, int door_y, int color_code, BombPositionData& bombPosition, std::vector<Enemy>& enemies, int bomb_lvls[], int name_index, int bomb_RANGE[], float BOMB_TIMER[], int number_of_bombs);
};

#endif