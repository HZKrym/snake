#include <ncurses.h>
int WIDTH;
int HEIGHT;



int kbhit() {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void init_ui() {
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
  getmaxyx(stdscr, HEIGHT, WIDTH);
	refresh();
}

void putcharyx(unsigned char ch, int y, int x) {
  mvwprintw(stdscr, y, x, "%c", ch);
}
