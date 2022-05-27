#include "game.h"

void Game::add_rabbit(std::pair<size_t, size_t> coord) {
  rabbits_.push_back(coord);
}

void Game::add_rabbits(std::vector<std::pair<size_t, size_t>> arr) {
  for (auto el : arr) {
    rabbits_.push_back(el);
  }
}

std::vector<std::pair<size_t, size_t>> Game::getcoords() {
  std::vector<std::pair<size_t, size_t>> res;

  for (auto el : rabbits_)
    res.push_back(el);

  return res;
}

void Game::kill_rabbit(std::pair<size_t, size_t> coord) {
  rabbits_.remove(coord);
}

void Game::addRabbits(size_t num, size_t max_x, size_t max_y) {
  std::vector<std::pair<size_t, size_t>> fluffies;

  auto find_el = [](std::vector<std::pair<size_t, size_t>> vec, std::pair<size_t, size_t> elem) {
    for (auto el : vec) {
      if (el == elem)
        return true;
    }

    return false;
  };

  for (size_t i = 0; i < num; ++i) {
    std::pair<size_t, size_t> val = {0, 0};

    do {
      val = genrand_coord(max_y - 1, max_x - 1);
    } while (find_el(fluffies, val));

    add_rabbit(val);
  }
}

std::pair<size_t, size_t> Game::genrand_coord(size_t max_x, size_t max_y) {
  auto randgen = [](size_t max) {
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<size_t> uniform_dist(2, max);

    return uniform_dist(el);
  };

  return {randgen(max_x), randgen(max_y)};
}

std::vector<std::pair<size_t, size_t>> Game::shrekcoords() {
  std::vector<std::pair<size_t, size_t>> res;
  for (auto el : swamp_) {
    res.push_back(el);
  }

  return res;
}

void Game::addSwamp(size_t max_x, size_t max_y) {
  auto val = genrand_coord(max_y - 1, max_x - 1);
  swamp_.push_back(val);
}

void Game::almostdie(std::pair<size_t, size_t> coord) {
  rabbitstodie_.push_back(coord);
}

std::vector<std::pair<size_t, size_t>> Game::almostdead() {
  std::vector<std::pair<size_t, size_t>> res;

  for (auto elem : rabbitstodie_) {
    res.push_back(elem);
  }

  return res;
}

void Game::GrowSwamp(size_t max_y, size_t max_x) {
  auto res = shrekcoords();

  auto maxsize = res.size();

  auto randgen = [](size_t max) {
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<size_t> uniform_dist(0, max);

    return uniform_dist(el);
  };

  auto ind = randgen(maxsize - 1);
  auto coord = res[ind];

  auto direction = randgen(4);
  switch (direction) {
    case 0:
      swamp_.erase(swamp_.begin() + ind);
      if (!swamp_.size())
        addSwamp(max_y, max_x);
      break;
    case 1:
      if (coord.first + 1 != max_x && coord.first + 1 != 1)
        swamp_.push_back({coord.first + 1, coord.second});
      break;
    case 2:
      if (coord.first - 1 != max_x && coord.first - 1 != 1)
        swamp_.push_back({coord.first - 1, coord.second});
      break;
    case 3:
      if (coord.second + 1 != max_y && coord.second + 1 != 1)
        swamp_.push_back({coord.first, coord.second + 1});
      break;
    case 4:
      if (coord.second - 1 != max_x && coord.second - 1 != 1)
        swamp_.push_back({coord.first, coord.second - 1});
      break;

    default:
      break;
  }
}

void Game::clearalmostdead() {
  rabbitstodie_.clear();
};
