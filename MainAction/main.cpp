#include <cstring>
#include <iostream>

#include "../Gview/gview.h"
#include "../Tview/tview.h"
#include "../View/view.h"

int main(int argc, char* argv[]) {
  std::string type;
  if (argc == 1) {
    type = "text";
  } else {
    type = argv[1];
  }

  View* v = View::get(type);
  v->main_loop();

  return 0;
}
