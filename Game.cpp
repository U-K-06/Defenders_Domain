#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "Game.h"

#define GRID_SIZE 5
#define EMPTY ' ' 
#define PLAYER 'X'

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ESC 27

int Game::Run() {
    int playerX = 0;
    int playerY = 0;
    char input;

    while (1) {
        clearScreen();
        drawGrid(playerX, playerY);
        
        if (_kbhit()) {
            input = _getch();

            switch (input) {
            case UP_ARROW:
                if (playerY > 0) playerY--;
                break;
            case DOWN_ARROW:
                if (playerY < GRID_SIZE - 1) playerY++;
                break;
            case LEFT_ARROW:
                if (playerX > 0) playerX--;
                break;
            case RIGHT_ARROW: 
                if (playerX < GRID_SIZE - 1) playerX++;
                break;
            case ESC:
                return 0;
            }
        }
        Sleep(60);
    }

    return 0;
}

void Game::clearScreen() {
    system("cls");
}

void Game::drawGrid(int playerX, int playerY) {
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (x == playerX && y == playerY) {
                std::cout << PLAYER;
            }
            else {
                std::cout << EMPTY;
            }
        }
        printf("\n");
    }
}

