#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include <list>
#include <utility>

using rabbit = std::pair<int, int>;

class Game {
  std::list<rabbit> rabbits;
};

#endif  // MODEL_MODEL_H