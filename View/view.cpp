#include "view.h"

#include <termios.h>
#include <unistd.h>

#include <cstring>

#include "../Gview/gview.h"
#include "../Tview/tview.h"

View* View::obj = nullptr;
View* View::get(const std::string& rhs) {
  std::string text = "text";
  std::string goi = "goi";

  if (!obj) {
    if (rhs == text) {
      obj = new TView;
    } else if (rhs == goi) {
      obj = new GView;
    } else {
      std::cout << "Non-correct input" << std::endl;
      exit(-1);
    }
  }

  return obj;
}

void View::putc(char c) {
  std::cout << c << std::endl;
}

void View::puts(const std::string& st) {
  std::cout << st << std::endl;
}