#include "ui.h"
#include "engine.h"

int main(int argc, char const *argv[]) {
  initui();
  initgame();
  create_snake();
  
  while (check()) {
    print();
    if (kbhit()) keyboard(getKey());
    movesnake();
  }

  lose();
  return 0;
}