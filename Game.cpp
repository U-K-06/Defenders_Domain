#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "Game.h"
#include "constants.h"

int Game::Run() {
  int GRID_SIZE = calculateGrid();
  int playerX = 0;
  int playerY = 0;
  char input;
  
  while (1) {
    clearScreen();
    drawGrid(playerX, playerY, GRID_SIZE);
        
    if (_kbhit()) {
      input = _getch();
      switch (input) {
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

int Game::calculateGrid()
{
  int choice;
  int GRID_SIZE;
  std::cout << "ENTER THE GRID SIDE \n\t(0 -> 2x2)\n(1 -> 3x3)\n(2 -> 4x4)\n(3 -> 5x5)\n(4 -> 6x6)\n(5 -> 8x8)\n(6 -> 10x10)\n(7 -> CUSTOM GRID SIZE)\n(8 -> EXIT)\n";
  std::cout << "Enter Your Choice: ";
  std::cin >> choice;

  int gridOptions[] = {2,3,4,5,6,8,10};

  if (choice >= 0 && choice <= 6) GRID_SIZE = gridOptions[choice];
  
  else if (choice == 7) {
    int size;
    std::cout << "Enter Grid Size: ";
    std::cin >> size;
    GRID_SIZE = size;
    delete &size;
  }

  else return 0;
  
  return GRID_SIZE;
}

void Game::drawGrid(int playerX, int playerY, int GRID_SIZE) {  
  for (int j = 0; j <= 2 * GRID_SIZE; j++) {
    if (j % 2 == 0)
      std::cout << BORDER_CORNER;
    else
      std::cout << BORDER_WALL_X;
  }
  std::cout << std::endl;

  for (int i = 0; i <= 2 * GRID_SIZE; i++) {
    if (i % 2 != 0) {
      for (int j = 0; j <= 2 * GRID_SIZE; j++) {
        if (j % 2 == 0)
          std::cout << BORDER_WALL_Y;
        else
          std::cout << EMPTY;
      }
    } else {
        for (int j = 0; j <= 2 * GRID_SIZE; j++) {
          if (j == 0)
            std::cout << BORDER_CORNER;
          if (j % 2 == 0)
            std::cout << BORDER_CORNER;
          else
            std::cout << BORDER_WALL_X;
        }
    }
    std::cout << std::endl;
  }

  for (int j = 0; j <= 2 * GRID_SIZE; j++) {
    if (j % 2 == 0)
      std::cout << BORDER_CORNER;
    else
      std::cout << BORDER_WALL_X;
  }
  std::cout << std::endl;
}

