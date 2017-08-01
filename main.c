#include "ui.h"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum Direction { up, down, left, right };

struct Snake {
  int *x;
  int *y;
  int length;
  int size;
  enum Direction direction;
} snake;

struct Apple {
  int x;
  int y;
  char isBig;
} apple;



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

void keyboard(char ch) {
  switch(ch) {
    case 'w': if (snake.direction != down) snake.direction = up; break;
    case 's': if (snake.direction != up) snake.direction = down; break;
    case 'a': if (snake.direction != right) snake.direction = left; break;
    case 'd': if (snake.direction != left) snake.direction = right; break;
  }
}

void move_snake() {
  int i;
  for (i = snake.length - 1; i > 0; i--) {
    snake.x[i] = snake.x[i - 1];
    snake.y[i] = snake.y[i - 1];
  }
  switch(snake.direction) {
    case left:
      if (snake.x[0] != 0) {
        snake.x[0] -= 1;
      } else {
        snake.x[0] = WIDTH - 1;
      }
    break;
    case up:
      if (snake.y[0] != 1) {
        snake.y[0] -= 1;
      } else {
        snake.y[0] = HEIGHT - 1;
      }
    break;
    case right:
      if (snake.x[0] != WIDTH - 1) {
        snake.x[0] += 1;
      } else {
        snake.x[0] = 0;
      }
    break;
    case down:
      if (snake.y[0] != HEIGHT - 1) {
        snake.y[0] += 1;
      } else {
        snake.y[0] = 1;
      }
    break;
  }
}

void regenerate_apple() {
  if (rand() % 100 < 25) {
    apple.isBig = 1;
  } else {
    apple.isBig = 0;
  }
  do {
    apple.x = rand() % (WIDTH - 1);
    apple.y = rand() % (HEIGHT - 2) + 1;
  } while(mvinch(apple.y, apple.x) == mvinch(snake.y[1], snake.x[1]));
}

void check(char *game) {
  int i;
  for (i = 1; i < snake.length; i++) {
    if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) *game = 0;
  }
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
    memset(snake.x + snake.length - 1, 0, 5);
    memset(snake.y + snake.length - 1, 0, 5);
    regenerate_apple();
  }
}

void print() {
  int i;
  clear();
  attron(COLOR_PAIR(2));
  for (i = 0; i < snake.length; i++) {
    putcharyx('@', snake.y[i], snake.x[i]);
  }
  attroff(COLOR_PAIR(2));
  mvwprintw(stdscr, 0, 0, "Length: %d", snake.length);
  attron(COLOR_PAIR(3));
  if (apple.isBig) {
    putcharyx('&', apple.y, apple.x);
  } else {
    putcharyx('#', apple.y, apple.x);
  }
  attron(COLOR_PAIR(3));
  refresh();
}

int main(int argc, char const *argv[]) {
  char game_is_true = 1;

  srand(time(NULL));
  init_ui();

  apple.isBig = 0;
  apple.x = rand() % (WIDTH - 1);
  apple.y = rand() % (HEIGHT - 2) + 1;
  snake.length = 4;
  snake.size = 10;
  snake.direction = left;
  snake.x = (int*)malloc(sizeof(int) * snake.size);
  snake.y = (int*)malloc(sizeof(int) * snake.size);
  create_snake();

  while (game_is_true) {
    print();
    if (kbhit()) keyboard(getch());
    move_snake();
    check(&game_is_true);
  }

  free(snake.x);
  free(snake.y);
  endwin();
  return 0;
}
