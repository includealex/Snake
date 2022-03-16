#include "tview.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <ctime>
#include <iostream>

#include "../Model/model.h"
#include "../View/view.h"

#define FOREGROUND_COL_BLACK 30
#define FOREGROUND_COL_RED 31
#define FOREGROUND_COL_GREEN 32
#define FOREGROUND_COL_YELLOW 33
#define FOREGROUND_COL_BLUE 34
#define FOREGROUND_COL_MAGENTA 35
#define FOREGROUND_COL_CYAN 36
#define FOREGROUND_COL_WHITE 37

#define BACKGROUND_COL_BLACK 40
#define BACKGROUND_COL_RED 41
#define BACKGROUND_COL_GREEN 42
#define BACKGROUND_COL_YELLOW 43
#define BACKGROUND_COL_BLUE 44
#define BACKGROUND_COL_MAGENTA 45
#define BACKGROUND_COL_CYAN 46
#define BACKGROUND_COL_WHITE 47

struct termios old;
bool final = false;

TView::TView() {
  struct termios s;
  tcgetattr(0, &s);
  old = s;
  cfmakeraw(&s);
  s.c_lflag |= ISIG;
  tcsetattr(0, TCSANOW, &s);
  signal(SIGINT, Signhandler);
}

TView::~TView() {
  tcsetattr(0, TCSANOW, &old);
}

void TView::draw() {
  clear_screen();
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);
  draw_rabbit();
  box(w.ws_col, w.ws_row);

  setdefaultcolor();
}

void TView::main_loop() {
  int msectosleep = 500;

  while (!final) {
    struct pollfd a = {0, POLLIN};
    draw();
    fflush(stdout);

    if (poll(&a, 1, msectosleep) == 1) {
      char c;
      read(0, &c, 1);
      if (c == 'q') {
        break;
      }
    }
  }
}

void TView::setdefaultcolor() {
  printf("\e[m");
}

void TView::setcolor(int color) {
  printf("\e[%dm", color);
}

void TView::setcolor(int fcolor, int scolor) {
  printf("\e[%d;%dm", fcolor, scolor);
}

void TView::clear_screen() {
  printf("\e[H\e[J");
}

void TView::gocoord(int x, int y) {
  printf("\e[%d;%dH", y, x);
}

void TView::box(int x_length, int y_width) {
  setcolor(FOREGROUND_COL_BLACK, BACKGROUND_COL_CYAN);

  gocoord(1, 1);
  for (int i = 0; i < x_length; ++i) {
    printf(" ");
  }

  gocoord(1, y_width);
  for (int i = 0; i < x_length; ++i) {
    printf(" ");
  }

  for (int i = 1; i < y_width; ++i) {
    gocoord(1, i);
    printf(" ");
    gocoord(x_length, i);
    printf(" ");
  }
}

void TView::draw_rabbit() {
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);

  int x = rand() % (w.ws_col - 2) + 2;
  int y = rand() % (w.ws_row - 2) + 2;

  gocoord(x, y);
  setcolor(FOREGROUND_COL_YELLOW, BACKGROUND_COL_WHITE);
  printf("@");

  fflush(stdout);
}

void Signhandler(int n) {
  final = true;
}