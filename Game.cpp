#include <conio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <tuple>
#include <ctime>

#include "Game.h"
#include "draw.h"
#include "constants.h"

std::string tower_names[] = { "Electric Tower", "Fire Tower", "Poison Tower", "Water Tower", "Ice Tower", "Wind Tower", "Shadow Tower" };

std::string colors[] = { "\033[38;5;214m", "\033[38;5;196m", "\033[38;5;93m", "\033[38;5;39m", "\033[38;5;81m", "\033[38;5;159m", "\033[38;5;23m" };

int number_of_towers = sizeof(tower_names) / sizeof(tower_names[0]);

int Game::Run() {

  hide_cursor();

  int active_tower = 0, selection_tower = 0;
  bool is_place_mode_active = false;
  int active_grid_x = 0, active_grid_y = 0;

  char input;
  int GRID_SIZE, choice;
  std::tie(GRID_SIZE, choice) = calculate_grid();
  Draw draw;
  TowerPositionData TowerPosition;

  std::srand(time(0));

  Draw::m_enemy_type = enemy_type();
  Draw::m_enemy_color = enemy_color(choice);

  Enemy new_enemy;

  new_enemy.type  = enemy_type();
  new_enemy.color = enemy_color(choice);
  new_enemy.x     = rand() % (2 * GRID_SIZE + 1);
  new_enemy.y     = rand() % (2 * GRID_SIZE + 1);
  
  enemies.push_back(new_enemy);

  while (1) {
    clear_screen(GRID_SIZE);
    draw.grid(GRID_SIZE, tower_names, active_tower, selection_tower, active_grid_x, active_grid_y, is_place_mode_active, TowerPosition, enemies);

    for (auto& tower : TowerPosition)
    {
      time_t current_time = time(0);
      if (tower.level < 4 && (current_time - tower.last_upgrade_time) >= GameConstants::UPGRADE_TIMES[tower.index][tower.level]) 
      { 
        tower.level++; 
        tower.last_upgrade_time = current_time;
      }
    }

    if (_kbhit()) {
      input = _getch();
      switch (input) {
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
        case KeyBindings::COL_KEY:
        case KeyBindings::SPACE:
          if (!is_place_mode_active) {
            active_tower = selection_tower;
          } else {
            calculate_tower_positions(GRID_SIZE, active_tower, active_grid_x, active_grid_y, TowerPosition);
          }
          break;
        case KeyBindings::ESC:
          //display_tower_positions(TowerPosition);
          clear_screen(GRID_SIZE);
          return 0;
      }
    }
  }
  return 0;
}

void Game::toggle_state(bool& is_place_mode_active) { is_place_mode_active = !is_place_mode_active; }

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

int Game::enemy_type()
{
  return (rand() % (GameConstants::MAX_ENEMIES - 63)+64); 
}

std::string Game::enemy_color(int choice)
{
  return  (choice > 5) ? colors[rand() % sizeof(colors) / sizeof(colors[0])] : (choice > 1) ? colors[rand() % (choice-1)] : colors[0];
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

std::tuple<int, int> Game::calculate_grid()
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

  else return std::make_tuple(0, choice);

  system("cls");
  return std::make_tuple(GRID_SIZE, choice);
}

void Game::calculate_tower_positions(int GRID_SIZE, int active_tower, int active_grid_x, int active_grid_y, TowerPositionData& TowerPosition)
{
  TowerPositionDataStruct newTowerPosition;
  newTowerPosition.index             = active_tower;
  newTowerPosition.x                 = active_grid_x;
  newTowerPosition.y                 = active_grid_y;
  newTowerPosition.last_upgrade_time = time(0);


  TowerPosition.push_back(newTowerPosition);
  placed_towers_list.push_back(newTowerPosition);
}

void Game::display_tower_positions(const TowerPositionData& TowerPosition)
{
  std::cout << "Tower Posistions: \n";
  for (const auto& tower : TowerPosition) {
    std::cout << "Tower: " << tower.index << ", Coord: [" << tower.x << ", " << tower.y << "]" << std::endl;
  }
}

