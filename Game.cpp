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
        case KeyBindings::COL_KEY:
        case KeyBindings::Q_KEY:
        case KeyBindings::q_KEY:
          toggle_state(is_place_mode_active);
          break;
        case KeyBindings::J_KEY:
        case KeyBindings::j_KEY:
        case KeyBindings::W_KEY:
        case KeyBindings::w_KEY:
        case KeyBindings::UP_ARROW:
          Move(is_place_mode_active, "UP", active_grid_y, active_grid_x, selection_tower, number_of_towers, GRID_SIZE);
          break;
        case KeyBindings::K_KEY:
        case KeyBindings::S_KEY:
        case KeyBindings::s_KEY:
        case KeyBindings::DOWN_ARROW:
          Move(is_place_mode_active, "DOWN", active_grid_y, active_grid_x, selection_tower, number_of_towers, GRID_SIZE);
          break;
        case KeyBindings::H_KEY:
        case KeyBindings::h_KEY:
        case KeyBindings::a_KEY:
        case KeyBindings::A_KEY:
        case KeyBindings::LEFT_ARROW:
          Move(is_place_mode_active, "LEFT", active_grid_y, active_grid_x, selection_tower, number_of_towers, GRID_SIZE);
          break;
        case KeyBindings::L_KEY:
        case KeyBindings::D_KEY:
        case KeyBindings::d_KEY:
        case KeyBindings::RIGHT_ARROW:
            Move(is_place_mode_active, "RIGHT", active_grid_y, active_grid_x, selection_tower, number_of_towers, GRID_SIZE);
          break;
        case KeyBindings::ENTER:
          active_tower = selection_tower;
          break;
        case KeyBindings::ESC:
          return 0;
      }
    }
  }
  return 0;
}

void Game::toggle_state(bool& is_place_mode_active)
{
  if (!is_place_mode_active) is_place_mode_active = true;
  else is_place_mode_active = false;
}

void Game::Move(bool is_place_mode_active, std::string direction, int& active_grid_y, int& active_grid_x, int& selection_tower, int number_of_towers, int GRID_SIZE)
{
  if (is_place_mode_active)
  {
    if (direction == "UP")
    {
      (active_grid_y > 0) ? active_grid_y-- : active_grid_y = GRID_SIZE - 1;
    }
    if (direction == "DOWN")
    {
      active_grid_y++;
      active_grid_y = active_grid_y % GRID_SIZE;
    }
    if (direction == "LEFT")
    {
      (active_grid_x > 0) ? active_grid_x-- : active_grid_x = GRID_SIZE - 1;
    }
    if (direction == "RIGHT")
    {
      active_grid_x++;
      active_grid_x = active_grid_x % GRID_SIZE;
    }
  } else {
    if (direction == "UP")
    {
      selection_tower = selection_tower % number_of_towers;
      (selection_tower > 0) ? selection_tower-- : selection_tower = number_of_towers-1;
    }
    if (direction == "DOWN")
    {
      selection_tower++;
      selection_tower = selection_tower % number_of_towers;
    }
  }
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
