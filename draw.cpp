#include <iostream>

#include "draw.h"
#include "constants.h"

void Draw::grid(int GRID_SIZE, std::string tower_names[], int active_tower, int selection_tower)
{
  int name_index = 0;
  std::cout << "\n\n\n\n\n";
  // TODO: We will get 2D array (calculateTowerPositions) and draw grid based on it;
  for (int i = 0; i <= 2 * GRID_SIZE; i++) {
    if (i <= 1) {
      std::cout << "\t\t\t\t\t\t\t\t";
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
    } else {
      if (i % 2 != 0) {
        if (!tower_names[name_index].empty()) {
          if (name_index == selection_tower) { std::cout << "\t\t\t\033[34m" << tower_names[name_index] << "\t\t\t\t\033[37m"; name_index++; }
          else if (name_index == active_tower) { std::cout << "\t\t\t\033[32m" << tower_names[name_index] << "\t\t\t\t\033[37m"; name_index++; }
          else { std::cout << "\t\t\t" << tower_names[name_index] << "\t\t\t\t"; name_index++; }
        }
        else std::cout << "\t\t\t\t\t\t\t\t";
        for (int j = 0; j <= 2 * GRID_SIZE; j++) {
          if (j % 2 == 0)
            std::cout << BORDER_WALL_Y;
          else
            std::cout << EMPTY;
        }
      } else {
          std::cout << "\t\t\t\t\t\t\t\t";
          for (int j = 0; j <= 2 * GRID_SIZE; j++) {
            if (j % 2 == 0)
              std::cout << BORDER_CORNER;
            else
              std::cout << BORDER_WALL_X;
          }
      }
    }
    std::cout << '\n';  
  }
}
