#pragma once

#ifndef GAME_H
#define GAME_H

class Game {
public:
    int Run(); 
    void clearScreen();
    int calculateGrid();
    void drawGrid(int playerX, int playerY, int GRID_SIZE);
};

#endif
