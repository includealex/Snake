#ifndef INCLUDES_GAME_H
#define INCLUDES_GAME_H

#include <vector>
#include <list>

class Game {
 public:
  std::vector<std::pair<size_t, size_t>> getcoords();
  void add_rabbit(std::pair<size_t, size_t> coord);
  void kill_rabbit(std::pair<size_t, size_t> coord);

 private:
  std::list<std::pair<size_t, size_t>> rabbits_;
};

#endif  // INCLUDES_GAME_H