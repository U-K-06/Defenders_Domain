#include <iostream>

#include "draw.h"
#include "constants.h"

void Draw::grid(int GRID_SIZE)
{
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
