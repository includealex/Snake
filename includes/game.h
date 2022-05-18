#ifndef INCLUDES_GAME_H
#define INCLUDES_GAME_H

#include <list>
#include <random>
#include <vector>

class Game {
 public:
  std::vector<std::pair<size_t, size_t>> getcoords();
  std::vector<std::pair<size_t, size_t>> shrekcoords();

  void add_rabbit(std::pair<size_t, size_t> coord);
  void add_rabbits(std::vector<std::pair<size_t, size_t>> arr);
  void kill_rabbit(std::pair<size_t, size_t> coord);
  void addRabbits(size_t num, size_t max_x, size_t max_y);
  void addSwamp(size_t max_x, size_t max_y);
  void GrowSwamp(size_t max_x, size_t max_y);
  void almostdie(std::pair<size_t, size_t> coord);
  std::vector<std::pair<size_t, size_t>> almostdead();
  void clearalmostdead();

 private:
  std::vector<std::pair<size_t, size_t>> rabbitstodie_;
  std::pair<size_t, size_t> genrand_coord(size_t max_x, size_t max_y);
  std::list<std::pair<size_t, size_t>> rabbits_;

  std::vector<std::pair<size_t, size_t>> swamp_;
};

#endif  // INCLUDES_GAME_H