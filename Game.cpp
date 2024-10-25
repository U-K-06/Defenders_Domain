#include <conio.h>
#include <iostream>
#include <windows.h>

#include "Game.h"
#include "draw.h"
#include "constants.h"

std::string towerNames[] = { "Electric Tower", "Fire Tower", "Poison Tower", "Water Tower" };

int Game::Run() {
  char input;
  int GRID_SIZE = calculateGrid();
  Draw draw;

  while (1) {
    clearScreen(GRID_SIZE);
    draw.grid(GRID_SIZE, towerNames);
    if (_kbhit()) {
      input = _getch();
      switch (input) {
        case Q_KEY:
          break;
        case UP_ARROW:
          break;
        case DOWN_ARROW:
          break;
        case LEFT_ARROW:
          break;
        case RIGHT_ARROW:
          break;
        case ENTER:
          break;
        case ESC:
          return 0;
      }
    }
    Sleep(250);
  }
  return 0;
}

void Game::clearScreen(int GRID_SIZE) {
  for (int blank = 0; blank <= 4; blank++) {
    std::cout << "\033[F";
  }

  for (int i=-1; i < 2 * GRID_SIZE; i++) {
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
  }

  else return 0;
  
  system("cls");

  return GRID_SIZE;
}

int** Game::calculateTowerPositions(int** grid)
{
  // TODO: We will determin the positions where we have to render the towers and then return that 2D array;
  return nullptr;
}
