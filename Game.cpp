#include <conio.h>
#include <iostream>
#include <future>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <tuple>
#include <chrono>
#include <ctime>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Game.h"
#include "draw.h"
#include "constants.h"

#pragma comment(lib, "User32.lib")

// std::string bomb_names[] = {"Electro bomb", "Fire bomb", "Poison bomb", "Water bomb", "Ice bomb", "Wind bomb" };
std::string bomb_names[] = {"Electro bomb", "Fire bomb", "Poison bomb", "Water bomb", "Ice bomb", "Wind bomb", "Shadow bomb"};

std::string colors[] = {
    "\033[38;5;214m",
    "\033[38;5;196m",
    "\033[38;5;93m",
    "\033[38;5;39m",
    "\033[38;5;81m",
    "\033[38;5;159m",
    "\033[38;5;23m"};

int number_of_bombs = sizeof(bomb_names) / sizeof(bomb_names[0]);
int placed_bombs_count = 0;

std::vector<BombPositionDataClass> placed_bombs;
std::vector<std::pair<int, int>> portal_corners;

Draw draw;

int Game::Run()
{
  simulateKeyPress(VK_OEM_MINUS, true);

  simulateKeyPress(VK_OEM_MINUS, true);

  PlaySound(Audio::BGM, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // IGNORE: Error in PlaySound function

  system("cls");

  draw.game_name();

  hide_cursor();

  float timeSinceLastSpawn = 0.0f, deltaTime = 0.1f;
  float currentSpawnInterval = GameConstants::INITIAL_SPAWN_INTERVAL;
  time_t last_upgrade_time = time(0);
  int BOMB_RANGE[7] = {1, 1, 1, 1, 1, 1, 1};
  int BOMB_LEVEL[7] = {0, 0, 0, 0, 0, 0, 0};
  float BOMB_TIMER[7] = {
      5,    // Electric bomb
      6.5,  // Fire bomb
      8.5,  // Poison bomb
      12,   // Water bomb
      10.8, // Ice bombe
      6,    // Wind bomb
      13.6  // Shadow bomb
  };
  int active_grid_x = 0, active_grid_y = 0, l_index = 0, active_bomb = 0, selection_bomb = 0;
  bool is_place_mode_active = false;
  char input;
  int GRID_SIZE, choice;
  std::tie(GRID_SIZE, choice) = calculate_grid();
  BombPositionData bombPosition;

  std::srand(static_cast<unsigned int>(std::time(0)));

  auto last_time = std::chrono::steady_clock::now(), timer_start_time = std::chrono::steady_clock::now();

  Draw::m_enemy_type = enemy_type();
  Draw::m_enemy_color = enemy_color(choice);

  int door_x = 2 + 2 * (rand() % (GRID_SIZE / 2 - 1)), door_y = 2 + 2 * (rand() % (GRID_SIZE / 2 - 1));

  portal_corners.push_back(std::make_pair(door_x + 1, door_y));     // Top-left
  portal_corners.push_back(std::make_pair(door_x + 2, door_y));     // Top-right
  portal_corners.push_back(std::make_pair(door_x + 1, door_y + 1)); // Bottom-left
  portal_corners.push_back(std::make_pair(door_x + 1, door_y + 1)); // Bottom-right

  int color_code = 91 + (rand() % 6);

  while (1)
  {
    ((rand() % 99) % 2 == 0) ? ((rand() % 101) % 2 == 0) ? color_code = 91 + (rand() % 6) : color_code : color_code;

    auto current_time = std::chrono::steady_clock::now();
    float elapsed_time = std::chrono::duration<float>(current_time - last_time).count();

    last_time = current_time;
    timeSinceLastSpawn += elapsed_time;

    if (elapsed_time >= GameConstants::TIME_TO_DECREASE_SPAWN_INTERVAL)
    {
      currentSpawnInterval -= GameConstants::SPAWN_INTERVAL_DECAY_RATE * (elapsed_time / GameConstants::TIME_TO_DECREASE_SPAWN_INTERVAL);
      if (currentSpawnInterval >= GameConstants::MIN_SPAWN_INTERVAL)
        currentSpawnInterval = GameConstants::MIN_SPAWN_INTERVAL;
    }

    time_t current_upgrade_time = time(0);

    if (difftime(current_upgrade_time, last_upgrade_time) >= (GameConstants::UPGRADE_TIME[l_index]))
    {
      int index = rand() % number_of_bombs;
      BOMB_LEVEL[index] = (BOMB_LEVEL[index] < GameConstants::MAX_BOMB_LEVEL[index]) ? BOMB_LEVEL[index] + 1 : BOMB_LEVEL[index];
      last_upgrade_time = current_upgrade_time;
      (l_index >= number_of_bombs) ? l_index : ++l_index;
      bool buff = ((1 + rand()) % 9) % 2 == 0;

      if (buff)
        BOMB_RANGE[index] += 1;
      else
      {
        int r_sec = 1 + rand() % 3;
        (BOMB_TIMER[index] - r_sec < GameConstants::MIN_BOMB_TIMER[index]) ? BOMB_TIMER[index] = GameConstants::MIN_BOMB_TIMER[index] : BOMB_TIMER[index] -= r_sec;
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

    draw.grid(GRID_SIZE,
              bomb_names,
              active_bomb,
              selection_bomb,
              active_grid_x,
              active_grid_y,
              is_place_mode_active,
              bombPosition,
              enemies,
              door_x,
              door_y,
              color_code,
              BOMB_LEVEL,
              BOMB_RANGE,
              BOMB_TIMER,
              number_of_bombs,
              timer_start_time,
              portal_corners);

    // for (Enemy &enemy : enemies)
    // {
    //   auto current_time = std::chrono::steady_clock::now();
    //   float elapsed_time = std::chrono::duration<float>(current_time - enemy.last_move_time).count();

      // int dx = door_x - enemy.x;
      // int dy = door_y - enemy.y;


    //   if (isEnemyInPortalCorners(portal_corners, enemy.x, enemy.y)) continue;

    //   if (!enemy.hasMoved)
    //   {
    //     if (elapsed_time >= (enemy.MOVEMENT_SPEED + 1))
    //     {
    //       (abs(dx) > abs(dy)) ? (dx > 0)
    //                                 ? enemy.x++
    //                                 : enemy.x--
    //                           : (dy > 0)
    //                               ? enemy.y++
    //                               : enemy.y--;
    //       enemy.hasMoved = true;
    //       enemy.last_move_time = current_time;

    //       if (isEnemyInPortalCorners(portal_corners, enemy.x, enemy.y)) 
    //       {
    //         std::cout << enemy.color << (char)(enemy.type) << "POS: " << enemy.x << ", " << enemy.y << GameConstants::RESET << " " << door_x << ", " << door_y;
    //         draw.lose_game();
    //       }
    //     }
    //   }
    //   else
    //   {
    //     if (elapsed_time >= enemy.MOVEMENT_SPEED)
    //     {
    //       if (abs(dx) > abs(dy))
    //         (dx > 0) ? enemy.x++ : enemy.x--;
    //       else
    //       {
    //         (dy > 0) ? enemy.y++ : enemy.y--;

    //         enemy.last_move_time = current_time;
    //         if (isEnemyInPortalCorners(portal_corners, enemy.x, enemy.y))
    //         {
    //           std::cout << enemy.color << (char)(enemy.type) << "POS: " << enemy.x << ", " << enemy.y << GameConstants::RESET << " " << door_x << ", " << door_y;
    //           draw.lose_game();
    //         }
    //       }
    //     }
    //   }
    // }

for (Enemy &enemy : enemies)
{
    auto current_time = std::chrono::steady_clock::now();
    float elapsed_time = std::chrono::duration<float>(current_time - enemy.last_move_time).count();

    // Find the nearest portal corner
    std::pair<int, int> nearest_corner = findNearestPortalCorner(portal_corners, enemy.x, enemy.y);
    int dx = nearest_corner.first - enemy.x;
    int dy = nearest_corner.second - enemy.y;

    if (isEnemyInPortalCorners(portal_corners, enemy.x, enemy.y)) { continue; }

    if (!enemy.hasMoved)
    {
        if (elapsed_time >= 6.0f)
        {
            if (abs(dx) > abs(dy)) {
                (dx > 0) ? enemy.x++ : enemy.x--;
            } else {
                (dy > 0) ? enemy.y++ : enemy.y--;
            }
            enemy.hasMoved = true;
            enemy.last_move_time = current_time;

            // Check if the enemy reaches the nearest portal corner
            if (isEnemyInPortalCorners(portal_corners, enemy.x, enemy.y))
            {
              std::cout << enemy.color << (char)(enemy.type) << "POS: " << enemy.x << ", " << enemy.y << GameConstants::RESET << " " << door_x << ", " << door_y;
                draw.lose_game();
                simulateKeyPress(VK_OEM_PLUS,true);
                simulateKeyPress(VK_OEM_PLUS,true);
                exit(0);
            }
            
            // std::cout << "Enemy position: (" << enemy.x << ", " << enemy.y << ")  Nearest corner: (" << nearest_corner.first << ", " << nearest_corner.second << ")" << std::endl;
        }
    }
    else
    {
        if (elapsed_time >= enemy.MOVEMENT_SPEED)
        {
            if (abs(dx) > abs(dy)) {
                (dx > 0) ? enemy.x++ : enemy.x--;
            } else {
                (dy > 0) ? enemy.y++ : enemy.y--;
            }
            enemy.last_move_time = current_time;

            // Check if the enemy reaches the nearest portal corner
            if (isEnemyInPortalCorners(portal_corners, enemy.x, enemy.y))
            {
              std::cout << enemy.color << (char)(enemy.type) << "POS: " << enemy.x << ", " << enemy.y << GameConstants::RESET << " " << door_x << ", " << door_y;
                draw.lose_game();
                simulateKeyPress(VK_OEM_PLUS,true);
                simulateKeyPress(VK_OEM_PLUS,true);
                exit(0);
            }

            // std::cout << "Enemy position: (" << enemy.x << ", " << enemy.y << ")  Nearest corner: (" << nearest_corner.first << ", " << nearest_corner.second << ")" << std::endl;
        }
    }
}

    for (auto it = bombPosition.begin(); it != bombPosition.end();)
    {
      time_t current_time = time(0);
      time_t placement_time = it->placement_time;
      int bomb_timer = BOMB_TIMER[it->getIndex()];

      if ((current_time - it->placement_time) >= BOMB_TIMER[it->getIndex()] + (int)(GRID_SIZE / 4))
      {
        it->explode(enemies,
                     BOMB_RANGE[it->getIndex()],
                     door_x,
                     door_y,
                     number_of_bombs,
                     bombPosition);
        it = bombPosition.erase(it);
      }
      else
        ++it;
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
        Move(is_place_mode_active,
             "UP",
             active_grid_y,
             active_grid_x,
             selection_bomb,
             number_of_bombs,
             GRID_SIZE);
        break;
      case KeyBindings::K_KEY:
      case KeyBindings::S_KEY:
      case KeyBindings::s_KEY:
      case KeyBindings::DOWN_ARROW:
        Move(is_place_mode_active,
             "DOWN",
             active_grid_y,
             active_grid_x,
             selection_bomb,
             number_of_bombs,
             GRID_SIZE);
        break;
      case KeyBindings::H_KEY:
      case KeyBindings::h_KEY:
      case KeyBindings::a_KEY:
      case KeyBindings::A_KEY:
      case KeyBindings::LEFT_ARROW:
        Move(is_place_mode_active,
             "LEFT",
             active_grid_y,
             active_grid_x,
             selection_bomb,
             number_of_bombs,
             GRID_SIZE);
        break;
      case KeyBindings::L_KEY:
      case KeyBindings::D_KEY:
      case KeyBindings::d_KEY:
      case KeyBindings::RIGHT_ARROW:
        Move(is_place_mode_active,
             "RIGHT",
             active_grid_y,
             active_grid_x,
             selection_bomb,
             number_of_bombs,
             GRID_SIZE);
        break;
      case KeyBindings::COL_KEY:
      case KeyBindings::SPACE_KEY:
        if (!is_place_mode_active) active_bomb = selection_bomb;
        else
        {
          if (!Draw::is_bomb_placed(active_grid_x * 2, active_grid_y * 2, bombPosition))
          {
            if (active_bomb == 6) {
              srand(time(0));
              int random_bomb = rand() % (number_of_bombs-1);
              int dx = active_grid_x, dy = active_grid_y;
              int random = rand() % 3;
              int sign = rand() % 2 ? 1 : -1;

              dx += (random == 0) ? sign : 0;
              dy += (random == 1) ? sign : 0;
              if (random == 2)
              {
                dx += sign;
                dy += sign;
              }
              calculate_bomb_positions(GRID_SIZE,
                                      active_bomb,
                                      dx,
                                      dy,
                                      bombPosition);
        
            }
            
            calculate_bomb_positions(GRID_SIZE,
                                    active_bomb,
                                    active_grid_x,
                                    active_grid_y,
                                    bombPosition);
            placed_bombs_count++;
          }
        }
        break;
      case KeyBindings::ESC_KEY:
        draw.lose_game();
        simulateKeyPress(VK_OEM_PLUS,true);
        simulateKeyPress(VK_OEM_PLUS,true);
        exit(0);
        PlaySound(NULL, NULL, 0);

        return 0;
      default:
        input -= 48;
        if (input > 0 && input <= number_of_bombs)
          active_bomb = (input - 1);
      }
    }
  }

  return 0;
}

void Game::toggle_state(bool &is_place_mode_active) const { is_place_mode_active = !is_place_mode_active; }

void Game::Move(bool is_place_mode_active,
                std::string direction,
                int &active_grid_y,
                int &active_grid_x,
                int &selection_bomb,
                int number_of_bombs,
                int GRID_SIZE)
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

void Game::simulateKeyPress(WORD virtualKey, bool ctrl) {
    if (ctrl) { keybd_event(VK_CONTROL, 0, 0, 0); }

    keybd_event(virtualKey, 0, 0, 0);

    keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);

    if (ctrl) { keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); }
}

float Game::calculateDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

std::pair<int, int> Game::findNearestPortalCorner(const std::vector<std::pair<int, int>>& portal_corners, int x, int y) {
    std::pair<int, int> nearest_corner = portal_corners[0];
    float min_distance = calculateDistance(x, y, portal_corners[0].first, portal_corners[0].second);

    for (const auto& corner : portal_corners) {
        float distance = calculateDistance(x, y, corner.first, corner.second);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_corner = corner;
        }
    }

    return nearest_corner;
}

int Game::enemy_type()
{
  return (rand() % (GameConstants::MAX_ENEMIES - 63) + 64);
}

std::string Game::enemy_color(int choice)
{
  return (choice > 5) ? colors[rand() % sizeof(colors) / sizeof(colors[0])]
         : (choice > 1)
             ? colors[rand() % (choice - 1)]
             : colors[0];
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
  std::cout << "\n\n\n\nENTER THE GRID SIZE \n\t(0 -> 4x4)\n\t(1 -> 5x5)\n\t(2 -> 6x6)\n\t(3 -> 8x8)\n\t(4 -> 10x10)\n\t(5 -> CUSTOM GRID SIZE)\n\t(6 -> EXIT)\n";
  std::cout << "Enter Your Choice: ";
  std::cin >> choice;

  int grid_options[] = {4, 5, 6, 8, 10};

  if (choice >= 0 && choice <= 4)
    GRID_SIZE = grid_options[choice];

  else if (choice == 5)
  {
    int size;
    std::cout << "Enter Grid Size (Max -> 15): ";
    std::cin >> size;
    (size <= 15) ? GRID_SIZE = size : GRID_SIZE = 15;
  }

  else if (choice == 6)
    exit(0);

  else
    return std::make_tuple(0, choice);

  return std::make_tuple(GRID_SIZE, choice);
}

void Game::calculate_bomb_positions(int GRID_SIZE,
                                    int active_bomb,
                                    int active_grid_x,
                                    int active_grid_y,
                                    BombPositionData &bombPosition)
{
  Bomb bomb(active_bomb);
  BombPositionDataClass newbombPosition(active_bomb,
                                        active_grid_x,
                                        active_grid_y,
                                        bomb,
                                        time(0));

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

bool Game::isEnemyInPortalCorners(const std::vector<std::pair<int, int>> &portal_corners, int enemy_x, int enemy_y)
{
  std::pair<int, int> enemy_position = std::make_pair(enemy_x, enemy_y);
  // std::cout << (int)(std::find(portal_corners.begin(), portal_corners.end(), enemy_position) != portal_corners.end()) << std::endl;
  return std::find(portal_corners.begin(), portal_corners.end(), enemy_position) != portal_corners.end();
}