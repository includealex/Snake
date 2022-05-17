#include "game.h"

void Game::add_rabbit(std::pair<size_t, size_t> coord) {
  rabbits_.push_back(coord);
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