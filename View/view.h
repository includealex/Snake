#ifndef VIEW_H
#define VIEW_H

#include <cstring>
#include <iostream>

class View {
 public:
  static View* get(const std::string& rhs);

  virtual void main_loop() = 0;
  virtual void draw() = 0;

 private:
  void putc(char c);
  void puts(const std::string& st);

  static View* obj;
  int data_;
};

#endif  // VIEW_H