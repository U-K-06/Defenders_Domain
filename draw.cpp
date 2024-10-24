#include <iostream>

#include "draw.h"
#include "constants.h"

void Draw::grid(int GRID_SIZE, std::string towerNames[])
{
  for (int blank = 0; blank <= 2; blank++) {
    std::cout << '\n';
  }
  // TODO: We will get 2D array (calculateTowerPositions) and draw grid based on it;
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
          if (j % 2 == 0)
            std::cout << BORDER_CORNER;
          else
            std::cout << BORDER_WALL_X;
        }
    }
    std::cout << '\n';
  }
}
