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