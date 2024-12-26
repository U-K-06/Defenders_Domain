#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <string>
// #include <unistd.h>
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
  for (char c : GameConstants::__game_title__) {
      if (_kbhit()) {
        char input = _getch();
        switch (input) {
          case KeyBindings::ENTER_KEY:
            isCompleted = true;
            break;
        }
      }
    color_code = ((rand() % 99) % 2 == 0) ? ((rand() % 101) % 2 == 0 ? 91 + (rand() % 6) : color_code) : color_code;
    std::cout << "\033[" << color_code << "m" << c << GameConstants::RESET << std::flush;
    if (!Draw::isCompleted) {
      auto end = std::chrono::steady_clock::now();
      while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < (1 + (rand() % 6))) { 
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
  for (char c : GameConstants::__game_lose__) {
    color_code = ((rand() % 99) % 2 == 0) ? ((rand() % 101) % 2 == 0 ? 91 + (rand() % 6) : color_code) : color_code;
    std::cout << "\033[" << color_code << "m" << c << GameConstants::RESET << std::flush;
  }
  exit(0);
}

void Draw::grid(int GRID_SIZE, std::string tower_names[], int active_tower, int selection_tower, int active_grid_x, int active_grid_y, bool is_place_mode_active, TowerPositionData TowerPosition, std::vector<Enemy>& enemies, int door_x, int door_y, int color_code, std::vector<Bullet>& bullets)
{
    int name_index = 0;
    std::cout << "Enemies are like: (" << m_enemy_color << static_cast<char>(m_enemy_type) << GameConstants::RESET << ")\n--> The color indicates the type of tower that is the enemy's weakness.\n" << "The ASCII code represents the enemy's health (HP): " << m_enemy_type << std::endl;
    std::cout << "\n";
    for (int i = 0; i <= 2 * GRID_SIZE; i++) {
        if (i <= 1) {
            top_grid(i, GRID_SIZE, is_place_mode_active, active_grid_x, active_grid_y, TowerPosition, enemies, door_x, door_y, color_code);
        } else {
          if (i % 2 != 0) {
            if (!tower_names[name_index].empty()) {
              render_tower_names(name_index, selection_tower, active_tower, is_place_mode_active, tower_names);
            }
            else {
                std::cout << "\t\t\t\t\t\t\t\t";
            }       
            mid_grid(i, selection_tower, active_tower, is_place_mode_active, GRID_SIZE, active_grid_x, active_grid_y, door_x, door_y, color_code, TowerPosition, enemies);
          } else {
              bottom_grid(i, GRID_SIZE, is_place_mode_active, active_grid_x, active_grid_y, TowerPosition, enemies);
            }
        }
        std::cout << '\n';
    }
    render_bullets(bullets);
}

std::string Draw::place_tower(int index, int level)
{
  std::string tower;

  switch(index) {
    case 0:
     tower = GameConstants::ELECTRIC_TOWERS[level];
     break;
    case 1:
     tower = GameConstants::FIRE_TOWERS[level];
     break;
    case 2:
     tower = GameConstants::POISON_TOWERS[level];
     break;
    case 3:
     tower = GameConstants::WATER_TOWERS[level];
     break;
    case 4:
      tower = GameConstants::ICE_TOWERS[level];
      break;
    case 5:
      tower = GameConstants::WIND_TOWERS[level];
      break;
    case 6:
      tower = GameConstants::SHADOW_TOWERS[level];
      break;
    default:
      return GameConstants::EMPTY;  
  }

  return tower;
}

bool Draw::is_tower_placed(int x, int y, TowerPositionData& TowerPosition)
{
  for (const auto& tower : TowerPosition)
  {
    if (tower.getX() == x / 2 && tower.getY() == y / 2) return true;
  }
  return false;
}

int Draw::get_tower_index(int x, int y, TowerPositionData& TowerPosition)
{
  for (const auto& tower : TowerPosition)
  {
    if (tower.getX() == x / 2 && tower.getY() == y / 2) return tower.getIndex();
  }
  return -1;
}

int Draw::get_tower_level(int x, int y, TowerPositionData& TowerPosition)
{
  for (const auto& tower : TowerPosition)
  {
    if (tower.getX() == x / 2 && tower.getY() == y / 2) return tower.getLevel();
  }
  return -1;
}

void Draw::top_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, TowerPositionData TowerPosition, std::vector<Enemy>& enemies, int door_x, int door_y, int color_code) {
    std::cout << "\t\t\t\t\t\t\t\t";

    if (i % 2 != 0) {
      for (int j = 0; j <= 2 * GRID_SIZE; j++) {
          if (j % 2 == 0) {
            if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
              std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET; 
            } else {
              std::cout << GameConstants::BORDER_WALL_Y;
            }
          } else {
              if (j / 2 == door_x && i / 2 == door_y) {
                  std::cout << "\033[" + std::to_string(color_code) + "m" << GameConstants::DOOR << GameConstants::RESET;
              } else {
                  (is_tower_placed(j, i, TowerPosition)) ? std::cout << place_tower(get_tower_index(j, i, TowerPosition), get_tower_level(j, i, TowerPosition)) : std::cout << GameConstants::EMPTY;
              }
          }
      }
    } else {
        for (int j = 0; j <= 2 * GRID_SIZE; j++) {
            if (j % 2 == 0) {
                bool enemyAtPosition = false;
                for (const Enemy& enemy : enemies) {
                    if (enemy.x == j / 2 && enemy.y == i / 2) {
                        enemyAtPosition = true;
                        std::cout << enemy.color << static_cast<char>(enemy.type) << GameConstants::RESET;
                        break;
                    }

                }
                if (!enemyAtPosition) {
                    if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
                        std::cout << "\033[31m" << GameConstants::BORDER_CORNER << GameConstants::RESET;
                    } else {
                        std::cout << GameConstants::BORDER_CORNER;
                    }
                }
            } else {
                if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1))) {
                    std::cout << "\033[31m" << GameConstants::BORDER_WALL_X << GameConstants::RESET;
                } else {
                    std::cout << GameConstants::BORDER_WALL_X;
                }
            }
        }
    }
}

void Draw::render_tower_names(int& name_index, int selection_tower, int active_tower, bool is_place_mode_active, std::string tower_names[])
{
  if (name_index == selection_tower && !(is_place_mode_active)) {
      std::cout << "\t\t\t\033[34m" << tower_names[name_index] << "\t\t\t\t" << GameConstants::RESET;
      name_index++;
  }
  else if (name_index == active_tower) {
      std::cout << "\t\t\t\033[32m" << tower_names[name_index] << "\t\t\t\t" << GameConstants::RESET;
      name_index++;
  }
  else {
      std::cout << "\t\t\t" << tower_names[name_index] << "\t\t\t\t";
      name_index++;
  }
}

void Draw::bottom_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, TowerPositionData TowerPosition, std::vector<Enemy>& enemies) {
    std::cout << "\t\t\t\t\t\t\t\t";
    for (int j = 0; j <= 2 * GRID_SIZE; j++) {
        if (j % 2 == 0) {
            bool enemyAtPosition = false;
            for (const Enemy& enemy : enemies) {
                if (enemy.x == j / 2 && enemy.y == i / 2) {
                    enemyAtPosition = true;
                    std::cout << enemy.color << static_cast<char>(enemy.type) << GameConstants::RESET;
                    break;
                }
            }
            if (!enemyAtPosition) {
                if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
                    std::cout << "\033[31m" << GameConstants::BORDER_CORNER << GameConstants::RESET;
                } else {
                    std::cout << GameConstants::BORDER_CORNER;
                }
            }
        } else {
            if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1))) {
                std::cout << "\033[31m" << GameConstants::BORDER_WALL_X << GameConstants::RESET;
            } else {
                std::cout << GameConstants::BORDER_WALL_X;
            }
        }
    }
}

void Draw::mid_grid(int i, int selection_tower, int active_tower, bool is_place_mode_active, int GRID_SIZE, int active_grid_x, int active_grid_y, int door_x, int door_y, int color_code, TowerPositionData& TowerPosition, std::vector<Enemy>& enemies)
{
   for (int j = 0; j <= 2 * GRID_SIZE; j++) {
      if (j % 2 == 0) {
          if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
              std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << GameConstants::RESET;
          } else {
              std::cout << GameConstants::BORDER_WALL_Y;
          }
      } else {
          if (j / 2 == door_x && i / 2 == door_y) {
            std::cout << "\033[" + std::to_string(color_code) + "m" << GameConstants::DOOR << GameConstants::RESET;
          } else {
            (is_tower_placed(j, i, TowerPosition)) ? std::cout << place_tower(get_tower_index(j, i, TowerPosition), get_tower_level(j, i, TowerPosition)) : std::cout << GameConstants::EMPTY;
          }
        }
   }
}

void Draw::render_bullets(const std::vector<Bullet>& bullets) {
  for (const Bullet& bullet : bullets) {
   int bullet_x = bullet.getX();
   int bullet_y = bullet.getY();
   std::string color_code = "1;33";

   std::cout << "\033[" << color_code << "m" << "•" << GameConstants::RESET;
  }
}
