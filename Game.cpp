#include <conio.h>
#include <iostream>
#include <windows.h>

#include "Game.h"
#include "draw.h"
#include "constants.h"

std::string tower_names[] = { "Electric Tower", "Fire Tower", "Poison Tower", "Water Tower", "Ice Tower" };

int number_of_towers = sizeof(tower_names) / sizeof(tower_names[0]);

int Game::Run() {

  hide_cursor();

  int active_tower = 0, selection_tower = 0;
  bool is_place_mode_active = false;
  int active_grid_x = 0, active_grid_y = 0;

  char input;
  int GRID_SIZE = calculate_grid();
  Draw draw;

  while (1) {
    clear_screen(GRID_SIZE);
    draw.grid(GRID_SIZE, tower_names, active_tower, selection_tower, active_grid_x, active_grid_y, is_place_mode_active);
    if (_kbhit()) {
      input = _getch();
      switch (input) {
        case Q_KEY:
          if (!is_place_mode_active) is_place_mode_active = true;
          else is_place_mode_active = false;
          break;
        case UP_ARROW:
          if (is_place_mode_active) {
           (active_grid_y > 0) ? active_grid_y-- : active_grid_y = GRID_SIZE - 1; 
          } else {
            selection_tower = selection_tower % number_of_towers;
            (selection_tower > 0) ? selection_tower-- : selection_tower = number_of_towers-1;
          }
          break;
        case DOWN_ARROW:
          if (is_place_mode_active) {
            active_grid_y++;
            active_grid_y = active_grid_y % GRID_SIZE;
          } else {
            selection_tower++;
            selection_tower = selection_tower % number_of_towers;
          }
          break;
        case LEFT_ARROW:
          if (is_place_mode_active) {
            (active_grid_x > 0) ? active_grid_x-- : active_grid_x = GRID_SIZE - 1;
          }
          break;
        case RIGHT_ARROW:
          if (is_place_mode_active) {
            active_grid_x++;
            active_grid_x = active_grid_x % GRID_SIZE;
          }
          break;
        case ENTER:
          active_tower = selection_tower;
          break;
        case ESC:
          return 0;
      }
    }
  }
  return 0;
}

void Game::hide_cursor()
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursor_info;

  GetConsoleCursorInfo(out, &cursor_info);
  cursor_info.bVisible = false;
  SetConsoleCursorInfo(out, &cursor_info);
}

void Game::clear_screen(int GRID_SIZE) {
  for (int blank = 0; blank <= 4; blank++) {
    std::cout << "\033[F";
  }

  for (int i=-1; i < 2 * GRID_SIZE; i++) {
    std::cout << "\033[F";
  }
  std::cout << '\r';
}

int Game::calculate_grid()
{
  int choice;
  int GRID_SIZE;
  std::cout << "ENTER THE GRID SIDE \n\t(0 -> 2x2)\n\t(1 -> 3x3)\n\t(2 -> 4x4)\n\t(3 -> 5x5)\n\t(4 -> 6x6)\n\t(5 -> 8x8)\n\t(6 -> 10x10)\n\t(7 -> CUSTOM GRID SIZE)\n\t(8 -> EXIT)\n";
  std::cout << "Enter Your Choice: ";
  std::cin >> choice;

  int grid_options[] = {2,3,4,5,6,8,10};

  if (choice >= 0 && choice <= 6) GRID_SIZE = grid_options[choice];
 
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

int** Game::calculate_tower_positions(int** grid)
{
  // TODO: We will determin the positions where we have to render the towers and then return that 2D array;
  return nullptr; 
}
