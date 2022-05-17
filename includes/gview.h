#ifndef GVIEW_H
#define GVIEW_H

#include "view.h"

class GView : public View {
 public:
  ~GView() override {}
  virtual void draw();
  virtual void main_loop();
  void print_hello();
};

#endif  // GVIEW_H