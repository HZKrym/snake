#include "keyboard.h"
#include "engine.h"
#include <curses.h>

void keyboard(int ch) {
  switch(ch) {
    case KEY_UP: if (snake.direction != down) snake.direction = up; break;
    case KEY_DOWN: if (snake.direction != up) snake.direction = down; break;
    case KEY_LEFT: if (snake.direction != right) snake.direction = left; break;
    case KEY_RIGHT: if (snake.direction != left) snake.direction = right; break;
  }
}

int getKey(){
  return getch();
}