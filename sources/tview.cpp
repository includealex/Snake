#include "tview.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <ctime>
#include <iostream>

#include "game.h"
#include "model.h"

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


bool final = false;

TView::TView() {
  struct termios s;
  tcgetattr(0, &s);
  old_ = s;
  cfmakeraw(&s);
  s.c_lflag |= ISIG;
  tcsetattr(0, TCSANOW, &s);

  signal(SIGINT, Signhandler);
}

TView::~TView() {
  tcsetattr(0, TCSANOW, &old_);
}

void TView::draw() {
  clear_screen();
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);
  box(w.ws_col, w.ws_row);

  setdefaultcolor();
}

void TView::main_loop() {
  int msectosleep = 500;

  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);
  Snake snake({w.ws_col / 2, w.ws_row / 2});
  Snake snake2({w.ws_col / 2, w.ws_row / 2 + 1});

  Game process;
  addRabbits(process, nRabbits_);

  while (!final) {
    printf("\e[?25l");
    struct pollfd a = {0, POLLIN};
    draw();
    printSnake(snake);
    printSnake(snake2);
    printRabbits(process);
    fflush(stdout);

    if (poll(&a, 1, msectosleep) == 1) {
      printf("\007");
      char c;
      read(0, &c, 1);
      if (c == 'q') {
        clear_screen();
        printf("\e[?25h");
        break;
      }
      else {
        switch (c)
        {
        case 's':
          snake.setDirection(DOWN);
          break;
        case 'w':
          snake.setDirection(UP);
          break;
        case 'a':
          snake.setDirection(LEFT);
          break;
        case 'd':
          snake.setDirection(RIGHT);
          break;
        case 'k':
          snake2.setDirection(DOWN);
          break;
        case 'i':
          snake2.setDirection(UP);
          break;
        case 'j':
          snake2.setDirection(LEFT);
          break;
        case 'l':
          snake2.setDirection(RIGHT);
          break;

        default:
          break;
        }
      }
    }
    snakestep(snake, process);
    snakestep(snake2, process);

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

void Signhandler(int n) {
  printf("\e[H\e[J\e[?25h");
  final = true;
}

void TView::printSnake(Snake& snake) {
  auto body = snake.getcoord();

  for (size_t i = 0; i < body.size(); ++i) {
    gocoord(body[i].first, body[i].second);

    if (i) {
      setcolor(FOREGROUND_COL_BLACK, BACKGROUND_COL_CYAN);
      printf("#");
      continue;
    }

    setcolor(FOREGROUND_COL_BLACK, BACKGROUND_COL_GREEN);

    auto dir = snake.getDirection();
    switch (dir) {
      case RIGHT:
        printf(">");
        break;

      case LEFT:
        printf("<");
        break;

      case UP:
        printf("^");
        break;

      case DOWN:
        printf("v");
        break;

      default:
        printf(">");
        break;
    }
  }

  setdefaultcolor();
}

void TView::addRabbits(Game& game, size_t num) {
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);

  std::vector<std::pair<size_t, size_t>> fluffies;

  auto find_el = [](std::vector<std::pair<size_t, size_t>> vec, std::pair<size_t, size_t> elem) {
    for (auto el : vec) {
      if (el == elem)
        return true;
    }

    return false;
  };

  for (size_t i = 0; i < num; ++i) {
    std::pair<size_t, size_t> val = {0, 0};

    do {
      val = genrand_coord(w.ws_col - 1, w.ws_row - 1);
    } while (find_el(fluffies, val));

    game.add_rabbit(val);
  }
}

void TView::printRabbits(Game& game) {
  auto arr = game.getcoords();

  for (auto el : arr) {
    gocoord(el.first, el.second);
    setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_GREEN);
    printf("@");
  }

  setdefaultcolor();
}

bool TView::checkRabbit(Snake& snake, Game& game) {
  auto coord = snake.getcoordnexttohead();

  for(auto el : game.getcoords()) {
    if(coord == el)
      return true;
  }

  return false;
}

bool TView::checkbox(std::pair<size_t, size_t> coord) {
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);

  if(coord.second == 1 || coord.second == w.ws_row)
    return true;
  if(coord.first == 1 || coord.first == w.ws_col)
    return true;

  return false; 
}

bool TView::checkitself(Snake& snake) {
  auto val = snake.getcoordnexttohead();  
  auto arr = snake.getcoord();

  for(auto el : arr) {
    if(el == val)
      return true;
  }

  return false;
}

void TView::snakestep(Snake& snake, Game& game) {
  if(!snake.isalive())
    return;
  if(checkbox(snake.getcoordnexttohead()) || checkitself(snake)) {
    snake.killed();
    return;
  }

  if(checkRabbit(snake, game)) {
    auto val = snake.getcoordnexttohead();
    snake.addbody(val);
    game.kill_rabbit(val);
    addRabbits(game, 1);
  }

  snake.gonext();
}