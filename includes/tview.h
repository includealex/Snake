#ifndef TVIEW_H
#define TVIEW_H

#include <signal.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "game.h"
#include "model.h"
#include "view.h"

class TView final : public View {
 public:
  TView();
  ~TView() override;
  virtual void main_loop();

  struct termios old_;

 private:
  void draw();

  void gocoord(int x, int y);
  size_t nRabbits_ = 10;

  void printBox(int x_length, int y_width);
  void printSnake(Snake& snake);
  void printRabbits(Game& game);

  void setdefaultcolor();
  void setcolor(int color);
  void setcolor(int fcolor, int scolor);
  void clear_screen();
};

void Signhandler(int n);

#endif  // TVIEW_H