#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "Game.h"
#include "draw.h"
#include "constants.h"

int Game::Run() {
  int GRID_SIZE = calculateGrid();
  int playerX = 0;
  int playerY = 0;
  char input;
 
  Draw draw;

  while (1) {
    clearScreen(GRID_SIZE);
    draw.grid(GRID_SIZE);
    if (_kbhit()) {
      input = _getch();
      switch (input) {
      case ESC:
        return 0;
      }
    }
    Sleep(1000);
  }
  return 0;
}

void Game::clearScreen(int GRID_SIZE) {
  for (int i=-1; i < 2 * GRID_SIZE; i++)
  {
    std::cout << "\033[F";
  }
  std::cout << '\r';
}

int Game::calculateGrid()
{
  int choice;
  int GRID_SIZE;
  std::cout << "ENTER THE GRID SIDE \n\t(0 -> 2x2)\n\t(1 -> 3x3)\n\t(2 -> 4x4)\n\t(3 -> 5x5)\n\t(4 -> 6x6)\n\t(5 -> 8x8)\n\t(6 -> 10x10)\n\t(7 -> CUSTOM GRID SIZE)\n\t(8 -> EXIT)\n";
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
  
  system("cls");

  return GRID_SIZE;
}

