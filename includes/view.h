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

 private:
  virtual void draw() = 0;

  static View* obj;
};

#endif  // VIEW_H