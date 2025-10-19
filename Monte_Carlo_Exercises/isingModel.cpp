/**
 * @file isingModel.cpp
 * @brief Calculates the average spin of a square lattice of size L x L
 * at thermal equilibrium utilizing the Metropolis-Hastings algorithm.
 */

#include <array>
#include <cmath>
#include <iostream>
#include <random>

namespace Const {
const int latticeSize{50};
const double magField{0.0};
const double boltzmann{1.380649e-23};
const double temp{10};
const double beta{1.0 / (boltzmann * temp)};
const double epsilon{1.0};
const double spin{0.5};
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

// type alias for 2D array to increase readability
using Lattice =
    std::array<std::array<double, Const::latticeSize>, Const::latticeSize>;

/**
 * @brief Function sets the initial state of all lattice sites to spin up (+1/2)
 *
 * @param lattice the square periodic lattice of our system
 */
void setInitialState(Lattice &lattice) {
  for (int i = 0; i < Const::latticeSize; i++) {
    for (int j = 0; j < Const::latticeSize; i++) {
      lattice[i][j] = Const::spin;
    }
  }
}

int periodicIndex(int index, int size) { return (index + size) % size; }

/**
 * @brief Function calculates the change in energy from s -> s'
 *
 * @param lattice [square periodic lattice of our system]
 * @param i [the position along the x-axis]
 * @param j [the position along the y-axis]
 * @return [return the change in energy between s -> s']
 */
double deltaE(const Lattice &lattice, const int i, const int j) {
  double neighborSum = lattice[periodicIndex(i - 1, Const::latticeSize)][j] +
                       lattice[periodicIndex(i + 1, Const::latticeSize)][j] +
                       lattice[i][periodicIndex(j - 1, Const::latticeSize)] +
                       lattice[i][periodicIndex(j + 1, Const::latticeSize)];

  double state{lattice[i][j]};
  double result = 2 * state * (Const::epsilon * neighborSum + Const::magField);
  return result;
}

void equilibration(Lattice &lattice) {}
bool acceptabilityCheck() {
  double result{0.0};
  if (deltaE(i, j) > 0)
}

int main(void) {

  std::random_device rd;
  std::mt19937 gen(rd()); // seed

  // Generates random number for the xPos on the lattice
  std::uniform_int_distribution<> rndXPos(0, Const::latticeSize);
  // Generataes random number for the yPos on the lattice
  std::uniform_int_distribution<> rndYPos(0, Const::latticeSize);
  // Generates random number [0, 1) to compare with acceptance probability
  std::uniform_real_distribution<> rndNum(0, 1);

  // The 2D square lattice of size latticeSize x latticeSize
  Lattice lattice;
  setInitialState(lattice);

  return 0;
}
