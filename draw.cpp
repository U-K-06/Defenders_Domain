#include <iostream>

#include "draw.h"
#include "constants.h"

// TODO: Convert this code into more smaller functions;

void Draw::grid(int GRID_SIZE, std::string tower_names[], int active_tower, int selection_tower, int active_grid_x, int active_grid_y, bool is_place_mode_active)
{
  int name_index = 0;
  std::cout << "\n\n\n\n\n";
  // TODO: We are getting active x and y for grid and we have to color them as blinking red color for that box;
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
          if (name_index == selection_tower && !(is_place_mode_active)) { std::cout << "\t\t\t\033[34m" << tower_names[name_index] << "\t\t\t\t\033[37m"; name_index++; }
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
