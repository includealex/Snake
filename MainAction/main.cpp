#include <cstring>
#include <iostream>

#include "gview.h"
#include "model.h"
#include "tview.h"
#include "view.h"

int main(int argc, char* argv[]) {
  std::string type = (argc == 1) ? "text" : argv[1];

  View* v = View::get(type);
  v->main_loop();

  delete v;
}