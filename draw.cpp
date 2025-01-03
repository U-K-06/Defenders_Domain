#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <string>
#include "draw.h"
#include "constants.h"
#include "Game.h"

std::string Draw::m_enemy_color = "";
int Draw::m_enemy_type = 0;

void Draw::game_name()
{
  Game::hide_cursor();
  int color_code = 91 + (rand() % 6);
  auto start = std::chrono::steady_clock::now();
  for (char c : GameConstants::__game_title__)
  {
    if (_kbhit())
    {
      char input = _getch();
      switch (input)
      {
      case KeyBindings::ENTER_KEY:
        isCompleted = true;
        break;
      }
    }
    color_code = ((rand() % 99) % 2 == 0) ? ((rand() % 101) % 2 == 0 ? 91 + (rand() % 6) : color_code) : color_code;
    std::cout << "\033[" << color_code << "m" << c << GameConstants::RESET << std::flush;
    if (!Draw::isCompleted)
    {
      auto end = std::chrono::steady_clock::now();
      while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < (1 + (rand() % 5)))
      {
        end = std::chrono::steady_clock::now();
      }
      start = std::chrono::steady_clock::now();
    }
  }
}

void Draw::lose_game()
{
  Game::hide_cursor();
  int color_code = 91 + (rand() % 6);
  for (char c : GameConstants::__game_lose__)
  {
    color_code = ((rand() % 99) % 2 == 0) ? ((rand() % 101) % 2 == 0 ? 91 + (rand() % 6) : color_code) : color_code;
    std::cout << "\033[" << color_code << "m" << c << GameConstants::RESET << std::flush;
  }
  exit(0);
}

void Draw::grid(int GRID_SIZE, std::string bomb_names[], int active_bomb, int selection_bomb, int active_grid_x, int active_grid_y, bool is_place_mode_active, BombPositionData BombPosition, std::vector<Enemy> &enemies, int door_x, int door_y, int color_code, int BOMB_LEVEL[], int BOMB_RANGE[], float BOOM_TIMER[], int number_of_bombs)
{
  int name_index = 0;
  std::cout << "\n";
  for (int i = 0; i <= 2 * GRID_SIZE; i++)
  {
    if (i <= 1)
    {
      top_grid(i, GRID_SIZE, is_place_mode_active, active_grid_x, active_grid_y, BombPosition, enemies, door_x, door_y, color_code, BOMB_LEVEL);
    }
    else
    {
      if (i % 2 != 0)
      {
        if (!bomb_names[name_index].empty())
        {
          render_bomb_names(name_index, selection_bomb, active_bomb, is_place_mode_active, bomb_names, BOMB_LEVEL);
        }
        else
        {
          std::cout << "\t\t\t\t\t\t\t\t";
        }
        mid_grid(i, selection_bomb, active_bomb, is_place_mode_active, GRID_SIZE, active_grid_x, active_grid_y, door_x, door_y, color_code, BombPosition, enemies, BOMB_LEVEL, name_index, BOMB_RANGE, BOOM_TIMER, number_of_bombs);
      }
      else
      {
        bottom_grid(i, GRID_SIZE, is_place_mode_active, active_grid_x, active_grid_y, BombPosition, enemies, door_x, door_y, color_code);
      }
    }
    std::cout << '\n';
  }
}

std::string Draw::place_bomb(int index, int bomb_lvls[])
{
  std::string tower;

  switch (index)
  {
    case 0: return GameConstants::ELECTRO_BOMBS[bomb_lvls[index]];
    case 1: return GameConstants::FIRE_BOMBS[bomb_lvls[index]];
    case 2: return GameConstants::POISON_BOMBS[bomb_lvls[index]];
    case 3: return GameConstants::WATER_BOMBS[bomb_lvls[index]];
    case 4: return GameConstants::ICE_BOMBS[bomb_lvls[index]];
    case 5: return GameConstants::WIND_BOMBS[bomb_lvls[index]];
    case 6: return GameConstants::SHADOW_BOMBS[bomb_lvls[index]];
    default: return GameConstants::EMPTY;
  }

  return tower;
}

bool Draw::is_bomb_placed(int x, int y, BombPositionData &BombPosition)
{
  for (const auto &tower : BombPosition)
  {
    if (tower.getX() == x / 2 && tower.getY() == y / 2)
      return true;
  }
  return false;
}

int Draw::get_bomb_index(int x, int y, BombPositionData &BombPosition)
{
  for (const auto &tower : BombPosition)
  {
    if (tower.getX() == x / 2 && tower.getY() == y / 2)
      return tower.getIndex();
  }
  return -1;
}

int Draw::get_bomb_level(int x, int y, BombPositionData &BombPosition)
{
  for (const auto &tower : BombPosition)
  {
    if (tower.getX() == x / 2 && tower.getY() == y / 2);
      // return tower.getLevel();
  }
  return -1;
}

void Draw::top_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, BombPositionData BombPosition, std::vector<Enemy> &enemies, int door_x, int door_y, int color_code, int BOMB_LEVEL[])
{
  std::cout << "\t\t\t\t\t\t\t\t";

  if (i % 2 != 0)
  {

    for (int j = 0; j <= 2 * GRID_SIZE; j++)
    {
      if (j % 2 == 0)
      {
        if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y)))
        {
          (j == 2 * GRID_SIZE) ? std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET << "\t\t\t" << "LEVELS\t\tBUFFS[EXPLOSION TIME, AREA]" : std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET;
        }
        else
        {
          (j == 2 * GRID_SIZE) ? std::cout << GameConstants::BORDER_WALL_Y << "\t\t\t" << "LEVELS\t\tBUFFS[EXPLOSION TIME, AREA]" : std::cout << GameConstants::BORDER_WALL_Y;
        }
      } else (is_bomb_placed(j, i, BombPosition)) ? std::cout << place_bomb(get_bomb_index(j, i, BombPosition), BOMB_LEVEL) : std::cout << GameConstants::EMPTY;
    }
    
  }

  else
  {

    for (int j = 0; j <= 2 * GRID_SIZE; j++)
    {

      if (j % 2 == 0)
      {

        bool enemyAtPosition = false;

        for (const Enemy &enemy : enemies)
        {

          if (enemy.x == j / 2 && enemy.y == i / 2)
          {

            enemyAtPosition = true;

            std::cout << enemy.color << static_cast<char>(enemy.type) << GameConstants::RESET;

            break;
          }
        }

        if (!enemyAtPosition)
        {

          if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y)))
          {

            std::cout << "\033[31m" << GameConstants::BORDER_CORNER << GameConstants::RESET;
          }
          else
          {

            std::cout << GameConstants::BORDER_CORNER;
          }
        }
      }
      else
      {

        // Check for bullets in the positions where BORDER_WALL_X would be rendered

        if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1)))
        {

          std::cout << "\033[31m" << GameConstants::BORDER_WALL_X << GameConstants::RESET;
        }
        else
        {

          std::cout << GameConstants::BORDER_WALL_X;
        }
      }
    }
  }
}

void Draw::render_bomb_names(int& name_index, int selection_bomb, int active_bomb, bool is_place_mode_active, std::string bomb_names[], int bomb_lvls[])
{
  if (name_index == selection_bomb && !(is_place_mode_active))
  {
    std::cout << "\t\t\t\033[34m" << bomb_names[name_index] << "\t\t\t\t" << GameConstants::RESET;
    name_index++; 
  }
  else if (name_index == active_bomb)
  {
    std::cout << "\t\t\t\033[32m" << bomb_names[name_index] << "\t\t\t\t" << GameConstants::RESET;
    name_index++;
  }
  else
  {
    std::cout << "\t\t\t" << bomb_names[name_index] << "\t\t\t\t";
    name_index++;
  }
}

void Draw::bottom_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, BombPositionData BombPosition, std::vector<Enemy> &enemies, int door_x, int door_y, int color_code)
{
  std::cout << "\t\t\t\t\t\t\t\t";

  if (i % 2 != 0)
  {
    for (int j = 0; j <= 2 * GRID_SIZE; j++)
    {
      if (j % 2 == 0)
      {
        if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y)))
        {
          std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET;
        }
        else
        {
          std::cout << GameConstants::BORDER_WALL_Y;
        }
      }
    }
  }
  else
  {
    for (int j = 0; j <= 2 * GRID_SIZE; j++)
    {
      if (j % 2 == 0)
      {
        bool enemyAtPosition = false;
        for (const Enemy &enemy : enemies)
        {
          if (enemy.x == j / 2 && enemy.y == i / 2)
          {
            enemyAtPosition = true;
            std::cout << enemy.color << static_cast<char>(enemy.type) << GameConstants::RESET;
            break;
          }
        }

        if (!enemyAtPosition)
        {
          if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y)))
          {
            std::cout << "\033[31m" << GameConstants::BORDER_CORNER << GameConstants::RESET;
          }
          else
          {
            std::cout << GameConstants::BORDER_CORNER;
          }
        }
      }
      else
      {

        if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1)))
        {

          std::cout << "\033[31m" << GameConstants::BORDER_WALL_X << GameConstants::RESET;
        }
        else
        {

          std::cout << GameConstants::BORDER_WALL_X;
        }
      }
    }
  }
}
void Draw::mid_grid(int i, int selection_bomb, int active_bomb, bool is_place_mode_active, int GRID_SIZE, int active_grid_x, int active_grid_y, int door_x, int door_y, int color_code, BombPositionData &BombPosition, std::vector<Enemy> &enemies, int bomb_lvls[], int name_index, int BOMB_RANGE[], float BOOM_TIMER[], int number_of_bombs)
{
  int index = name_index - 1;
  for (int j = 0; j <= 2 * GRID_SIZE; j++)
  {
    if (j % 2 == 0)
    { 
      if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y)))
      {
        (j == 2 * GRID_SIZE && name_index < number_of_bombs) ?  std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET << "\t\t\t" << "( " << bomb_lvls[name_index] << " )" << "\t\t[ " << BOOM_TIMER[name_index] << BOMB_RANGE[name_index]  << " ]" : std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET;
      }
      else
      {
        (j == 2 * GRID_SIZE && name_index < number_of_bombs) ? std::cout << GameConstants::BORDER_WALL_Y << "\t\t\t" << "( " << bomb_lvls[name_index] << " )" << "\t\t[ " << BOOM_TIMER[name_index] << ", " << BOMB_RANGE[name_index]  << " ]" : std::cout << GameConstants::BORDER_WALL_Y;
      }
    }
    else
    {
      if (j / 2 == door_x && i / 2 == door_y)
      {
        std::cout << "\033[" + std::to_string(color_code) + "m" << GameConstants::DOOR << GameConstants::RESET;
      }
      else
      {
        (is_bomb_placed(j, i, BombPosition)) ? std::cout << place_bomb(get_bomb_index(j, i, BombPosition), bomb_lvls) : std::cout << GameConstants::EMPTY;
      }
    }
  }
}