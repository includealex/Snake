#include "view.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <cstring>
#include <random>
#include <vector>

#include "gview.h"
#include "tview.h"

View* View::obj = nullptr;
View* View::get(const std::string& rhs) {
  std::string text = "text";
  std::string goi = "goi";

  if (!obj) {
    if (rhs == text) {
      obj = new TView();
    } else if (rhs == goi) {
      obj = new GView();
    } else {
      std::cout << "Non-correct input" << std::endl;
      exit(-1);
    }
  }

  return obj;
}

View::View() {}