#pragma once

#ifndef GAME_H
#define GAME_H

class Game {
public:
    int Run();
    void hide_cursor();
    void clear_screen(int GRID_SIZE);
    int calculate_grid();
    int** calculate_tower_positions(int** grid);
};

#endif
