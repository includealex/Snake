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

std::pair<size_t, size_t> View::genrand_coord(size_t max_x, size_t max_y) {
  auto randgen = [](size_t max) {
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<size_t> uniform_dist(2, max);

    return uniform_dist(el);
  };

  return {randgen(max_x), randgen(max_y)};
}