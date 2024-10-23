#include <iostream>
#include <stdlib.h>

#include "Game.h"

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    if (std::string(argv[1]) == "help") {
      std::cout << "\t\tHelp Section";
    }
    else {
      Game game;
      game.Run();  
    }
  } else {
    system("PTD.exe");
  }
	return 0;
}
