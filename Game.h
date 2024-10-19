#pragma once

#ifndef GAME_H
#define GAME_H

class Game {
public:
    int Run(); 
    void clearScreen(); 
    void drawGrid(int playerX, int playerY);
};

#endif
