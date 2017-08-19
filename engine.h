#pragma once
#include "keyboard.h"


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

void movesnake();
char check();
void regenerate_apple();
void lose();
void initgame();
void create_snake();
void check_apple();