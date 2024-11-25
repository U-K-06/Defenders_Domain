#pragma once

#include "game.h"

class Bullet {
public:
    Bullet(int x, int y, Enemy* target, int damage, const std::string& color_code)
        : x(x), y(y), target(target), damage(damage), color_code(color_code) {}

    void update() {
      if (target) {
        if (x < target->x)  x++;
        else if (x > target->x) x--;

        if (y < target->y)  y++;
        else if (y > target->y) y--;
      }
    }

    bool checkCollision() {
      return target && target->x == x && target->y == y;
    }

    void applyDamage() {
      if (target) {
        target->takeDamage(damage); 
      }
    }

    bool isOutOfBounds(int GRID_SIZE) {
      return (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE);
    }

    int getX() const { return x; }
    int getY() const { return y; }
    const std::string& getColorCode() const { return color_code; };

private:
  int x, y;
  Enemy* target;
  int damage;
  std::string color_code;
};
