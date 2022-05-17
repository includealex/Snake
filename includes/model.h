#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include <cstring>
#include <vector>

#include "game.h"
#include "view.h"

enum Direction { RIGHT = -1, LEFT = 1, UP = -2, DOWN = 2 };

class Snake {
 public:
  Snake(std::pair<size_t, size_t> startcoord);

  Direction getDirection() const;
  std::pair<size_t, size_t> getheadcoord();
  std::vector<std::pair<size_t, size_t>> getcoord() const;

  bool isalive();

  void setDirection(Direction d);
  void addbody(std::pair<size_t, size_t> coord);

  void snakestep(Game& game, Snake& snake2, size_t max_x, size_t max_y);

 private:
  Direction dir_ = RIGHT;
  std::list<std::pair<size_t, size_t>> snake_body_;
  bool alive_ = true;

  void gonext();
  void die(Game& Game);
  bool checkSnake2(Snake& snake2);
  bool checkbox(size_t max_x, size_t max_y);
  bool checkRabbit(Game& game);
  bool checkitself();
  std::pair<size_t, size_t> getcoordnexttohead();
};

#endif  // MODEL_MODEL_H