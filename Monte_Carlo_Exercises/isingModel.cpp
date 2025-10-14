#include <array>
#include <iostream>
#include <random>
#include <vector>

namespace Constants {
const int latticeSize{50};
}

int main(void) {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> rndXPos(-Constants::latticeSize,
                                          Constants::latticeSize);
  std::uniform_int_distribution<> rndYPos(-Constants::latticeSize,
                                          Constants::latticeSize);

  std::array<std::array<double, Constants::latticeSize>, Constants::latticeSize>
      lattice;

  return 0;
}
