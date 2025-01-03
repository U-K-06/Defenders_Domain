#include <conio.h>
#include <iostream>
#include <future>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <tuple>
#include <chrono>
#include <ctime>
#include <cmath>
#include "Game.h"
#include "draw.h"
#include "constants.h"

std::string bomb_names[] = {"Electro bomb", "Fire bomb", "Poison bomb", "Water bomb", "Ice bomb", "Wind bomb", "Shadow bomb"};

std::string colors[] = {"\033[38;5;214m", "\033[38;5;196m", "\033[38;5;93m", "\033[38;5;39m", "\033[38;5;81m", "\033[38;5;159m", "\033[38;5;23m"};

int number_of_bombs = sizeof(bomb_names) / sizeof(bomb_names[0]);
int placed_bombs_count = 0;

std::vector<BombPositionDataClass> placed_bombs;

Draw draw;

int Game::Run()
{
  // PlaySound(Audio::BGM, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // IGNORE: Error in PlaySound function
  system("cls");
  SetConsoleFontSize(25);
  draw.game_name();
  hide_cursor();

  float deltaTime = 0.1f;
  float currentSpawnInterval = GameConstants::INITIAL_SPAWN_INTERVAL;
  float timeSinceLastSpawn = 0.0f;

  time_t last_upgrade_time = time(0);

  int BOMB_RANGE[7]    = { 1, 1, 1, 1, 1, 1, 1 };
  int BOMB_LEVEL[7]    = { 0, 0, 0, 0, 0, 0, 0 };

  float BOMB_TIMER[7] = {
                                      5,    // Electric bomb
                                      6.5,  // Fire bomb
                                      8.5,  // Poison bomb
                                      10,   // Water bomb
                                      10.8, // Ice bomb
                                      11.6, // Wind bomb
                                      12.6  // Shadow bomb
                                    };

  int l_index = 0;
  
  int active_bomb = 0, selection_bomb = 0;
  bool is_place_mode_active = false;
  int active_grid_x = 0, active_grid_y = 0;

  char input;
  int GRID_SIZE, choice;
  std::tie(GRID_SIZE, choice) = calculate_grid();
  BombPositionData bombPosition;

  std::srand(static_cast<unsigned int>(std::time(0)));

  auto last_time = std::chrono::steady_clock::now();

  Draw::m_enemy_type = enemy_type();
  Draw::m_enemy_color = enemy_color(choice);

  int door_x = 2 + 2 * (rand() % (GRID_SIZE / 2 - 1)), door_y = 2 + 2 * (rand() % (GRID_SIZE / 2 - 1));

  int color_code = 91 + (rand() % 6);

  while (1)
  {

    ((rand() % 99) % 2 == 0) ? ((rand() % 101) % 2 == 0) ? color_code = 91 + (rand() % 6) : color_code : color_code;

    auto current_time = std::chrono::steady_clock::now();
    float elapsed_time = std::chrono::duration<float>(current_time - last_time).count();

    last_time = current_time;

    timeSinceLastSpawn += elapsed_time;

    if (elapsed_time >= GameConstants::TIME_TO_DECREASE_SPAWN_INTERVAL) {
      currentSpawnInterval -= GameConstants::SPAWN_INTERVAL_DECAY_RATE * (elapsed_time / GameConstants::TIME_TO_DECREASE_SPAWN_INTERVAL);
      if (currentSpawnInterval >= GameConstants::MIN_SPAWN_INTERVAL) {
        currentSpawnInterval = GameConstants::MIN_SPAWN_INTERVAL;
      }
    }

    time_t current_upgrade_time = time(0);

    if (difftime(current_upgrade_time, last_upgrade_time) >= (GameConstants::UPGRADE_TIME[l_index]))
    {
      int index = rand() % number_of_bombs;
      BOMB_LEVEL[index] = (BOMB_LEVEL[index] < GameConstants::MAX_BOMB_LEVEL[index]) ? BOMB_LEVEL[index] + 1 : BOMB_LEVEL[index];
      last_upgrade_time = current_upgrade_time;
      (l_index >= number_of_bombs) ? l_index : ++l_index;
      bool buff = ((1+rand()) % 9) % 2 == 0;
      if (buff) {
        BOMB_RANGE[index] += 1;
      }
      else{
        int r_sec = 1 + rand() % 3;
        (BOMB_TIMER[index]-r_sec < GameConstants::MIN_BOMB_TIMER[index]) ? BOMB_TIMER[index] = GameConstants::MIN_BOMB_TIMER[index] : BOMB_TIMER[index] -= r_sec;
      }
    }

    if (timeSinceLastSpawn >= currentSpawnInterval)
    {
      Enemy new_enemy;

      new_enemy.type = enemy_type();
      new_enemy.color = enemy_color(choice);

      if (rand() % 2 == 0)
      {
        new_enemy.x = rand() % ((2 * GRID_SIZE));
        new_enemy.y = (rand() % 2 == 0) ? 0 : ((2 * GRID_SIZE));
      }
      else
      {
        new_enemy.x = (rand() % 2 == 0) ? 0 : ((2 * GRID_SIZE));
        new_enemy.y = rand() % ((2 * GRID_SIZE));
      }

      enemies.push_back(new_enemy);

      timeSinceLastSpawn = 0.0f;
    }

    clear_screen(GRID_SIZE);
    draw.grid(GRID_SIZE, bomb_names, active_bomb, selection_bomb, active_grid_x, active_grid_y, is_place_mode_active, bombPosition, enemies, door_x, door_y, color_code, BOMB_LEVEL, BOMB_RANGE, BOMB_TIMER, number_of_bombs);

    for (Enemy &enemy : enemies)
    {
      auto current_time = std::chrono::steady_clock::now();
      float elapsed_time = std::chrono::duration<float>(current_time - enemy.last_move_time).count();

      int dx = door_x - enemy.x;
      int dy = door_y - enemy.y;

      if (!enemy.hasMoved)
      {
        if (elapsed_time >= 6.0f)
        {
          if (abs(dx) > abs(dy))
          {
            (dx > 0) ? enemy.x++ : enemy.x--;
          }
          else
          {
            (dy > 0) ? enemy.y++ : enemy.y--;
          }
          enemy.hasMoved = true;
          enemy.last_move_time = current_time;

          if (enemy.x == door_y - 1 && enemy.y == door_y - 1)
          {
            draw.lose_game();
          }
        }
      }
      else
      {
        if (elapsed_time >= 5.0f)
        {
          if (abs(dx) > abs(dy))
          {
            (dx > 0) ? enemy.x++ : enemy.x--;
          }
          else
          {
            (dy > 0) ? enemy.y++ : enemy.y--;

            enemy.last_move_time = current_time;

            if (enemy.x == door_y && enemy.y == door_y)
            {
              draw.lose_game();
            }
          }
        }
      }
    }

    for (auto it = bombPosition.begin(); it != bombPosition.end();)
    {
        time_t current_time = time(0);
        time_t placement_time = it->placement_time;
        int bomb_timer = BOMB_TIMER[it->getIndex()];

        if ((current_time - it->placement_time) >= BOMB_TIMER[it->getIndex()] + (int)(GRID_SIZE/4))
        {
            it->explode(enemies, BOMB_RANGE[it->getIndex()]);
            it = bombPosition.erase(it);
        }
        else  ++it;
    }

    if (_kbhit())
    {
      input = _getch();
      switch (input)
      {
      case KeyBindings::Q_KEY:
      case KeyBindings::q_KEY:
        toggle_state(is_place_mode_active);
        break;
      case KeyBindings::J_KEY:
      case KeyBindings::j_KEY:
      case KeyBindings::W_KEY:
      case KeyBindings::w_KEY:
      case KeyBindings::UP_ARROW:
        Move(is_place_mode_active, "UP", active_grid_y, active_grid_x, selection_bomb, number_of_bombs, GRID_SIZE);
        break;
      case KeyBindings::K_KEY:
      case KeyBindings::S_KEY:
      case KeyBindings::s_KEY:
      case KeyBindings::DOWN_ARROW:
        Move(is_place_mode_active, "DOWN", active_grid_y, active_grid_x, selection_bomb, number_of_bombs, GRID_SIZE);
        break;
      case KeyBindings::H_KEY:
      case KeyBindings::h_KEY:
      case KeyBindings::a_KEY:
      case KeyBindings::A_KEY:
      case KeyBindings::LEFT_ARROW:
        Move(is_place_mode_active, "LEFT", active_grid_y, active_grid_x, selection_bomb, number_of_bombs, GRID_SIZE);
        break;
      case KeyBindings::L_KEY:
      case KeyBindings::D_KEY:
      case KeyBindings::d_KEY:
      case KeyBindings::RIGHT_ARROW:
        Move(is_place_mode_active, "RIGHT", active_grid_y, active_grid_x, selection_bomb, number_of_bombs, GRID_SIZE);
        break;
      case KeyBindings::COL_KEY:
      case KeyBindings::SPACE_KEY:
        if (!is_place_mode_active)
        {
          active_bomb = selection_bomb;
        }
        else
        {
          if (!Draw::is_bomb_placed(active_grid_x * 2, active_grid_y * 2, bombPosition))
          {
            calculate_bomb_positions(GRID_SIZE, active_bomb, active_grid_x, active_grid_y, bombPosition);
            placed_bombs_count++;
          }
        }
        break;
      case KeyBindings::ESC_KEY:
        draw.lose_game();
        PlaySound(NULL, NULL, 0);
        return 0;
      }
    }
  }
  return 0;
}

void Game::toggle_state(bool &is_place_mode_active) const { is_place_mode_active = !is_place_mode_active; }

void Game::Move(bool is_place_mode_active, std::string direction, int &active_grid_y, int &active_grid_x, int &selection_bomb, int number_of_bombs, int GRID_SIZE)
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
  }
  else
  {
    if (direction == "UP")
    {
      selection_bomb = selection_bomb % number_of_bombs;
      (selection_bomb > 0) ? selection_bomb-- : selection_bomb = number_of_bombs - 1;
    }
    if (direction == "DOWN")
    {
      selection_bomb++;
      selection_bomb = selection_bomb % number_of_bombs;
    }
  }
}

int Game::enemy_type()
{
  return (rand() % (GameConstants::MAX_ENEMIES - 63) + 64);
}

std::string Game::enemy_color(int choice)
{
  return (choice > 5) ? colors[rand() % sizeof(colors) / sizeof(colors[0])] : (choice > 1) ? colors[rand() % (choice - 1)] : colors[0];
}

void SetConsoleFontSize(int fontSize) {
  CONSOLE_FONT_INFOEX cfi;
  
  cfi.nFont        = 0;
  cfi.dwFontSize.X = 0;
  cfi.dwFontSize.Y = fontSize;
  cfi.FontFamily   = FF_DONTCARE;
  cfi.FontWeight   = FW_NORMAL;
  
  std::wcscpy(cfi.FaceName, L"Consolas");
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfi); 
}

void Game::hide_cursor()
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursor_info;

  GetConsoleCursorInfo(out, &cursor_info);
  cursor_info.bVisible = false;
  SetConsoleCursorInfo(out, &cursor_info);
}

void Game::clear_screen(int GRID_SIZE)
{
  static bool is_cleared = false;
  std::cout << "\033[26;H";
  if (!is_cleared)
  {
    std::cout << "\033[J";
    is_cleared = true;
  }
  std::cout << '\r';
}

std::tuple<int, int> Game::calculate_grid()
{
  int choice;
  int GRID_SIZE;
  std::cout << "\n\n\n\nENTER THE GRID SIZE \n\t(0 -> 2x2)\n\t(1 -> 3x3)\n\t(2 -> 4x4)\n\t(3 -> 5x5)\n\t(4 -> 6x6)\n\t(5 -> 8x8)\n\t(6 -> 10x10)\n\t(7 -> CUSTOM GRID SIZE)\n\t(8 -> EXIT)\n";
  std::cout << "Enter Your Choice: ";
  std::cin >> choice;

  int grid_options[] = { 2, 3, 4, 5, 6, 8, 10 };

  if (choice >= 0 && choice <= 6)
    GRID_SIZE = grid_options[choice];

  else if (choice == 7)
  {
    // TODO: Add a limit to max grid size and also change the font size based on the grid size to make it fit in screen
    int size;
    std::cout << "Enter Grid Size: ";
    std::cin >> size;
    GRID_SIZE = size;
  }

  else
    return std::make_tuple(0, choice);

  // system("cls");

  return std::make_tuple(GRID_SIZE, choice);
}

void Game::calculate_bomb_positions(int GRID_SIZE, int active_bomb, int active_grid_x, int active_grid_y, BombPositionData &bombPosition)
{
  Bomb bomb(active_bomb);
  BombPositionDataClass newbombPosition(active_bomb, active_grid_x, active_grid_y, bomb, time(0));

  bombPosition.push_back(newbombPosition);
  placed_bombs_list.push_back(newbombPosition);
}

void Game::display_bomb_positions(const BombPositionData &bombPosition)
{
  std::cout << "bomb Posistions: \n";
  for (const auto &bomb : bombPosition)
  {
    std::cout << "bomb: " << bomb.getIndex() << ", Coord: [" << bomb.getX() << ", " << bomb.getY() << "]" << std::endl;
  }
}