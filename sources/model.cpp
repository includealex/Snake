#include "model.h"

#include <random>

Snake::Snake(std::pair<size_t, size_t> startcoord) {
  snake_body_.push_back(startcoord);
  snake_body_.push_back({startcoord.first - 1, startcoord.second});
  snake_body_.push_back({startcoord.first - 2, startcoord.second});
  snake_body_.push_back({startcoord.first - 3, startcoord.second});
  snake_body_.push_back({startcoord.first - 4, startcoord.second});
}

void Snake::setDirection(Direction d) {
  if (d == -dir_)
    return;

  dir_ = d;
}

std::vector<std::pair<size_t, size_t>> Snake::getcoord() const {
  std::vector<std::pair<size_t, size_t>> res;

  for (auto el : snake_body_)
    res.push_back(el);

  return res;
}

Direction Snake::getDirection() const {
  return dir_;
}

void Snake::gonext() {
  auto val = snake_body_.front();
  snake_body_.pop_back();

  switch (dir_) {
    case RIGHT:
      val.first += 1;
      break;

    case LEFT:
      val.first -= 1;
      break;

    case UP:
      val.second -= 1;
      break;

    case DOWN:
      val.second += 1;
      break;

    default:
      break;
  }

  snake_body_.push_front(val);
}

std::pair<size_t, size_t> Snake::getheadcoord() {
  return snake_body_.front();
}

std::pair<size_t, size_t> Snake::getcoordnexttohead() {
  auto val = getheadcoord();
  switch (dir_)
  {
  case RIGHT:
    val.first += 1;
    break;
  case LEFT:
    val.first -= 1;
    break;  
  case UP:
    val.second -= 1;
    break;
  case DOWN:
    val.second += 1;
    break;        
  default:
    break;
  }

  return val;
}

void Snake::addbody(std::pair<size_t, size_t> coord) {
  snake_body_.push_back(coord);
}

void Snake::killed() {
  snake_body_.empty();
  alive_ = false;
}

bool Snake::isalive() {
  return alive_;
}