#pragma once

#ifndef GAME_H
#define GAME_H

class Game {
public:
    int Run();
    void toggle_state(bool& is_place_mode_active);
    void Move(bool is_place_mode_active, std::string direction, int& active_grid_y, int& active_grid_x, int& selection_tower, int number_of_towers, int GRID_SIZE);
    void hide_cursor();
    void clear_screen(int GRID_SIZE);
    int calculate_grid();
    int** calculate_tower_positions(int** grid);
};

#endif
