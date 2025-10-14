#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

namespace Const {
const int latticeSize{50};
const double magField{0.0};
const double boltzmann{1.380649e-23};
const double temp{10};
const double beta{1.0 / (boltzmann * temp)};
const double epsilon{1.0};

} // namespace Const

/* TODO
 * - Construct function to calculate acceptance probability and then
 * accepts or rejects the spin flip
 * - devise efficient loop for the equilibration of the lattice system
 * - devise efficient loop for the commiting the Metropolis-Hastings
 * algorithm on our lattice
 * - calculate the <s_i> average spin of our lattice after N steps as a
 * function of B, epsilon, and T.
 */

// Template for 2D array to increase readability
using Lattice =
    std::array<std::array<double, Const::latticeSize>, Const::latticeSize>;

/*
 * 
void equilibration(Lattice& lattice){


}
int main(void) {

  std::random_device rd;
  std::mt19937 gen(rd()); // seed

  // Generates randum number for the xPos on the latice
  std::uniform_int_distribution<> rndXPos(0, Const::latticeSize);
  // Generataes random number for the yPos on the lattice
  std::uniorm_int_distribution<> rndYPos(0, Const::latticeSize);
  // Generates random number [0, 1) to compared with acceptance probability
  std::uniform_real_distribution<> rndNum(0, 1);

  // The 2D square lattice of size latticeSize x latticeSize
  Lattice lattice;

  return 0;
}
