#include "model.h"

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

  return val;
}

void Snake::addbody(std::pair<size_t, size_t> coord) {
  snake_body_.push_back(coord);
}

void Snake::die(Game& game) {
  game.add_rabbits(getcoord());

  snake_body_.clear();
  alive_ = false;
}

bool Snake::isalive() {
  return alive_;
}

bool Snake::checkitself() {
  auto val = getcoordnexttohead();
  auto arr = getcoord();

  for (auto el : arr) {
    if (el == val)
      return true;
  }

  return false;
}

bool Snake::checkRabbit(Game& game) {
  auto coord = getcoordnexttohead();

  for (auto el : game.getcoords()) {
    if (coord == el)
      return true;
  }

  return false;
}

bool Snake::checkbox(size_t max_x, size_t max_y) {
  auto coord = getcoordnexttohead();

  if (coord.second == 1 || coord.second == max_x)
    return true;
  if (coord.first == 1 || coord.first == max_y)
    return true;

  return false;
}

bool Snake::checkSnake2(Snake& snake2) {
  auto val = getcoordnexttohead();
  auto arr2 = snake2.getcoord();

  for (auto el : arr2) {
    if (val == el)
      return true;
  }

  return false;
}

void Snake::snakestep(Game& game, Snake& snake2, size_t max_x, size_t max_y) {
  if (!isalive())
    return;

  auto arr = game.almostdead();
  for (auto krol : arr) {
    game.kill_rabbit(krol);
  }
  game.clearalmostdead();

  if (checkbox(max_x, max_y) || checkitself() || checkSnake2(snake2)) {
    die(game);
    return;
  }

  checkSwamp(game);

  if (checkRabbit(game)) {
    auto val = getcoordnexttohead();
    addbody(val);
    game.kill_rabbit(val);
    game.addRabbits(1, max_x, max_y);
  }
  if (!speed_)
    gonext();
}

bool Snake::checkSwamp(Game& game) {
  auto coord = getcoordnexttohead();
  auto arr = game.shrekcoords();
  auto rabbitarr = game.getcoords();

  for (auto elem : rabbitarr) {
    for (auto shr : arr) {
      if (elem == shr)
        game.almostdie(elem);
    }
  }

  for (auto el : arr) {
    if (el == coord) {
      speed_ += 1;
      speed_ %= 2;
      return true;
    }
  }

  return false;
}