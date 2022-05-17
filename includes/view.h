#ifndef VIEW_H
#define VIEW_H

#include <cstring>
#include <iostream>

class View {
 public:
  static View* get(const std::string& rhs);

  View();
  virtual ~View() {}

  virtual void main_loop() = 0;
  std::pair<size_t, size_t> genrand_coord(size_t max_x, size_t max_y);

 private:
  virtual void draw() = 0;

  static View* obj;
};

#endif  // VIEW_H