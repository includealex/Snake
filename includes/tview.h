#ifndef TVIEW_H
#define TVIEW_H

#include <signal.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>

#include "game.h"
#include "model.h"
#include "view.h"

class TView : public View {
 public:
  TView();
  ~TView() override;
  virtual void main_loop();

  struct termios old_;

  void snakestep(Snake& snake, Game& game);
 private:
  void draw();

  size_t nRabbits_ = 10;

  void gocoord(int x, int y);
  void box(int x_length, int y_width);
  void addRabbits(Game& game, size_t num);
  bool checkitself(Snake& snake);
  bool checkbox(std::pair<size_t, size_t> coord);
  bool checkRabbit(Snake& snake, Game& game);
  void printSnake(Snake& snake);
  void printRabbits(Game& game);

  void setdefaultcolor();
  void setcolor(int color);
  void setcolor(int fcolor, int scolor);
  void clear_screen();
};

void Signhandler(int n);

#endif  // TVIEW_H