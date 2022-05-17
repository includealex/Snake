#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include <list>
#include <set>
#include <utility>
#include <vector>

#include "view.h"

enum Direction { RIGHT = -1, LEFT = 1, UP = -2, DOWN = 2 };

class Snake {
 public:
  Snake(std::pair<size_t, size_t> startcoord);

  void setDirection(Direction d);
  void gonext();

  std::pair<size_t, size_t> getheadcoord();
  std::pair<size_t, size_t> getcoordnexttohead();
  Direction getDirection() const;
  std::vector<std::pair<size_t, size_t>> getcoord() const;
  void addbody(std::pair<size_t, size_t> coord);
  void killed();
  bool isalive();

 private:
  Direction dir_ = RIGHT;
  std::list<std::pair<size_t, size_t>> snake_body_;
  bool alive_ = true;
};

#endif  // MODEL_MODEL_H