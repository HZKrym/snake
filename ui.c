#include "ui.h"
#include "engine.h"
#include <curses.h>

int kbhit() {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void initui() {
    initscr();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    halfdelay(2);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    refresh();
}


void putcharyx(unsigned char ch, int y, int x) {
    mvwprintw(stdscr, y, x, "%c", ch);
}

void print() {
    int i;
    clear();
    for (i = 1; i <= HEIGHT; i++) {
      putcharyx('%', i, WIDTH);
      putcharyx('%', i, 0);
    }
    for (i = 0; i < WIDTH; i++) {
      putcharyx('%', HEIGHT, i);
      putcharyx('%', 1, i);
    }
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
    attroff(COLOR_PAIR(3));
    refresh();
  }