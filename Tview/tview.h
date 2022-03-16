#ifndef TVIEW_H
#define TVIEW_H

#include <signal.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>

#include "../Model/model.h"
#include "../View/view.h"

class TView : public View {
 public:
  TView();
  ~TView();
  virtual void main_loop();

 private:
  Game* fluffies;
  void gocoord(int x, int y);
  virtual void draw();
  void setdefaultcolor();
  void setcolor(int color);
  void setcolor(int fcolor, int scolor);
  void box(int x_length, int y_width);
  void draw_rabbit();
  void clear_screen();
};

void Signhandler(int n);

#endif  // TVIEW_H