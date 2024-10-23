#pragma once

#ifndef GAME_H
#define GAME_H

class Game {
public:
    int Run(); 
    void clearScreen(int GRID_SIZE);
    int calculateGrid();
    int** calculateTowerPositions(int** grid);
};

#endif
