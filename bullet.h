#pragma once

#include "Game.h"

class Bullet {
public:
    Bullet(int x, int y, Enemy* target, int damage)
        : x(x), y(y), target(target), damage(damage) {}

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

private:
  int x, y;
  Enemy* target;
  int damage;
};
