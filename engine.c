#include "engine.h"
#include "ui.h"
#include "keyboard.h"
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

void movesnake() {
  int i;
  for (i = snake.length - 1; i > 0; i--) {
    snake.x[i] = snake.x[i - 1];
    snake.y[i] = snake.y[i - 1];
  }
  switch(snake.direction) {
    case left:
      if (snake.x[0] != 1) {
        snake.x[0] -= 1;
      } else {
        snake.x[0] = WIDTH - 1;
      }
    break;

    case up:
      if (snake.y[0] != 2) {
        snake.y[0] -= 1;
      } else {
        snake.y[0] = HEIGHT - 1;
      }
    break;

    case right:
      if (snake.x[0] != WIDTH - 1) {
        snake.x[0] += 1;
      } else {
        snake.x[0] = 1;
      }
    break;

    case down:
      if (snake.y[0] != HEIGHT - 1) {
        snake.y[0] += 1;
      } else {
        snake.y[0] = 2;
      }
    break;
  }
  check_apple();
}
  
char check() {
  int i;
  for (i = 1; i < snake.length; i++) {
    if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) return 0;
  }    
  return 1;
}
  
void regenerate_apple() {
  if (rand() % 100 < 35) {
    apple.isBig = 1;
  } else {
    apple.isBig = 0;
  }
  do {
    apple.x = rand() % (WIDTH - 1) + 1;
    apple.y = rand() % (HEIGHT - 2) + 2;
  } while(mvinch(apple.y, apple.x) == mvinch(snake.y[1], snake.x[1]));
}

void lose() {
  free(snake.x);
  free(snake.y);
  
  mvwprintw(stdscr, HEIGHT / 2, WIDTH / 2 - 4, "You Lose!");
  refresh();
  halfdelay(100);
  getch();
  
  endwin();
}

void initgame() {
  srand(time(NULL));
  apple.isBig = 0;
  apple.x = rand() % (WIDTH - 1) + 1;
  apple.y = rand() % (HEIGHT - 2) + 2;
  snake.length = 4;
  snake.size = 10;
  snake.direction = left;
  snake.x = (int*)malloc(sizeof(int) * snake.size);
  snake.y = (int*)malloc(sizeof(int) * snake.size);
}
    
void create_snake() {
  snake.x[0] = WIDTH / 2 - 1;
  snake.y[0] = HEIGHT/ 2;
  snake.x[1] = WIDTH / 2;
  snake.y[1] = HEIGHT/ 2;
  snake.x[2] = WIDTH / 2 + 1;
  snake.y[2] = HEIGHT/ 2;
  snake.x[3] = WIDTH / 2 + 2;
  snake.y[3] = HEIGHT/ 2;
}

void check_apple() {
  int i;
  if (snake.x[0] == apple.x && snake.y[0] == apple.y) {
    if (apple.isBig) {
      snake.length += 5;
    } else {
      snake.length++;
    }
    if(snake.length >= snake.size) {
      snake.size *=2;
      snake.x = (int*)realloc(snake.x, sizeof(int) * snake.size);
      snake.y = (int*)realloc(snake.y, sizeof(int) * snake.size);
    }
    if (apple.isBig) {
      for (i = snake.length - 6; i < snake.length; i++) {
        snake.x[i] = 0;
        snake.y[i] = 0;
      }
    } else {
      snake.x[snake.length - 1] = 0;
      snake.y[snake.length - 1] = 0;
    }
      regenerate_apple();
  }
}