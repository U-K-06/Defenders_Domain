#include <iostream>
#include <random>
#include <vector>
#include <thread>

#include "draw.h"
#include "constants.h"
#include "Game.h"

std::string Draw::m_enemy_color = "";
int Draw::m_enemy_type = 0;

void Draw::grid(int GRID_SIZE, std::string tower_names[], int active_tower, int selection_tower, int active_grid_x, int active_grid_y, bool is_place_mode_active, TowerPositionData TowerPosition, int enemy_type, std::string enemy_color)
{
    int name_index = 0;
    std::cout << "Enemies are like: (" << enemy_color << static_cast<char>(m_enemy_type) << "\033[37m)\n--> The color indicates the type of tower that is the enemy's weakness.\n" << "The ASCII code represents the enemy's health (HP): " << m_enemy_type << std::endl;
    std::cout << "\n";
    for (int i = 0; i <= 2 * GRID_SIZE; i++) {
        if (i <= 1) {
            top_grid(i, GRID_SIZE, is_place_mode_active, active_grid_x, active_grid_y, TowerPosition);
        }
        else {
            if (i % 2 != 0) {
                if (!tower_names[name_index].empty()) {
                  render_tower_names(name_index, selection_tower, active_tower, is_place_mode_active, tower_names);
                }
                else {
                    std::cout << "\t\t\t\t\t\t\t\t";
                }

                for (int j = 0; j <= 2 * GRID_SIZE; j++) {
                    if (j % 2 == 0) {
                        if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
                            std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << "\033[37m";
                        } else {
                            std::cout << GameConstants::BORDER_WALL_Y;
                        }
                    }
                    else {
                        (is_tower_placed(j, i, TowerPosition)) ? std::cout << place_tower(get_tower_index(j, i, TowerPosition), get_tower_level(j, i, TowerPosition)) : std::cout << GameConstants::EMPTY;
                    }
                }
            }
            else {
                bottom_grid(i, GRID_SIZE, is_place_mode_active, active_grid_x, active_grid_y, TowerPosition);
            }
        }
        std::cout << '\n';
    }
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
    if (tower.x == x / 2 && tower.y == y / 2) return true;
  }
  return false;
}

int Draw::get_tower_index(int x, int y, TowerPositionData& TowerPosition)
{
  for (const auto& tower : TowerPosition)
  {
    if (tower.x == x / 2 && tower.y == y / 2) return tower.index;
  }
  return -1;
}

int Draw::get_tower_level(int x, int y, TowerPositionData& TowerPosition)
{
  for (const auto& tower : TowerPosition)
  {
    if (tower.x == x / 2 && tower.y == y / 2) return tower.level;
  }
  return -1;
}

void Draw::top_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, TowerPositionData TowerPosition) {
    std::cout << "\t\t\t\t\t\t\t\t";

    if (i % 2 != 0) {
        for (int j = 0; j <= 2 * GRID_SIZE; j++) {
            if (j % 2 == 0) {
                if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
                    std::cout << "\033[31m" << GameConstants::BORDER_WALL_Y << "\033[37m"; 
                } else {
                    std::cout << GameConstants::BORDER_WALL_Y;
                }
            } else {
              (is_tower_placed(j, i, TowerPosition)) ? std::cout << place_tower(get_tower_index(j, i, TowerPosition), get_tower_level(j, i, TowerPosition)) : std::cout << GameConstants::EMPTY;
            }
        }
    } else {
        for (int j = 0; j <= 2 * GRID_SIZE; j++) {
            if (j % 2 == 0) {
                if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
                    std::cout << "\033[31m" << GameConstants::BORDER_CORNER << "\033[37m";
                } else {
                    std::cout << GameConstants::BORDER_CORNER;
                }
            } else {
                if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1))) {
                    std::cout << "\033[31m" << GameConstants::BORDER_WALL_X << "\033[37m";
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
      std::cout << "\t\t\t\033[34m" << tower_names[name_index] << "\t\t\t\t\033[37m";
      name_index++;
  }
  else if (name_index == active_tower) {
      std::cout << "\t\t\t\033[32m" << tower_names[name_index] << "\t\t\t\t\033[37m";
      name_index++;
  }
  else {
      std::cout << "\t\t\t" << tower_names[name_index] << "\t\t\t\t";
      name_index++;
  }
}

void Draw::bottom_grid(int i, int GRID_SIZE, bool is_place_mode_active, int active_grid_x, int active_grid_y, TowerPositionData TowerPosition) {
    std::cout << "\t\t\t\t\t\t\t\t";

    for (int j = 0; j <= 2 * GRID_SIZE; j++) {
        if (j % 2 == 0) {
            if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1) || (j / 2 == active_grid_x + 1 && i / 2 == active_grid_y))) {
                std::cout << "\033[31m" << GameConstants::BORDER_CORNER << "\033[37m"; 
            } else {
                std::cout << GameConstants::BORDER_CORNER;
            }
        } else {
            if (is_place_mode_active && ((j / 2 == active_grid_x && i / 2 == active_grid_y) || (j / 2 == active_grid_x && i / 2 == active_grid_y + 1))) {
                std::cout << "\033[31m" << GameConstants::BORDER_WALL_X << "\033[37m"; 
            } else {
                std::cout << GameConstants::BORDER_WALL_X;
            }
        }
    }
}
