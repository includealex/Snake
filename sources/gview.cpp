#include "gview.h"

#include "view.h"

void GView::print_hello() {
  std::cout << "From gview "
            << "HELLO" << std::endl;
}

void GView::draw() {
  std::cout << "Don't look here" << std::endl;
}

void GView::main_loop() {
  std::cout << "not here" << std::endl;
}