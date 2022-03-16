#ifndef GVIEW_H
#define GVIEW_H

#include "../View/view.h"

class GView : public View {
 public:
  virtual void draw();
  virtual void main_loop();
  void print_hello();
};

#endif  // GVIEW_H