/**
 * @file isingModel.cpp
 * @brief Calculates the average spin of a square lattice of size L x L
 * at thermal equilibrium utilizing the Metropolis-Hastings algorithm.
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

namespace Const {
const int latticeSize{50};
const double magField{0.0};
const double boltzmann{1.0};
const double epsilon{1.0};
const double spin{1.0};
} // namespace Const

// type alias for 2D array to increase readability
using Lattice = std::vector<std::vector<double>>;

/*
 * @brief Function sets the initial state of all lattice sites to spin up
 * (+1/2)
 *
 * @param lattice: the square periodic lattice of our system
 */
void setInitialState(Lattice &lattice);

int periodicIndex(int index, int size);

/**
 * @brief Function calculates the change in energy from s -> s'
 *
 * @param lattice: square periodic lattice of our system
 * @param i: the position along the x-axis
 * @param j: the position along the y-axis
 *
 * @return return the change in energy between s -> s'
 */
double deltaE(const Lattice &lattice, const int &i, const int &j);

/**
 * @brief runs through the acceptibility check for the change in spin of a
 * lattice sight given the change in energy from s -> s'. If the change in
 * energy is negative, then the change is accepted as physical systems
 * prefer to be in a lower energy state.
 *
 * If dE is positive, we calculate an acceptance probability from the
 * Boltzmann distribution and then utilize a random uniform number from
 * [0,1] and compare it to the calculated acceptance. If this random uniform
 * number is less thant the acceptance probability, we flip the spin, else
 * there is no change.
 *
 * @param dE: the change in energy between s and s'
 * @param randomNumU: random uniform number [0,1]
 * @param beta: the betaerature of the system
 *
 * @return true or false, depending on acceptance
 */
bool acceptabilityCheck(const double &dE, const double &randomNumU,
                        const double &beta);

/**
 * @brief calculates the instantaneous sum of all our spins in the system
 *
 * @param lattice: square periodic lattice of our system
 *
 * @return: sum of spins in the system
 */
double calcInstTotalSpin(const Lattice &lattice);
/**
 * @brief function runs through the Metropolis-Hastings algorithm.
 * The default is for measurement to be set to false, so that we can place the
 * system into equilibrium.
 *
 * When measurement = true, the function will conduct measurements of the
 * simulated system.
 *
 * @param lattice: square periodic lattice of our system
 * @param numSteps: number of steps to run the Metropolis-Hastings algorithm
 * @param beta: inverse betaerature of our system
 * @param gen: std::mt19937 random number generator
 * @param takeMeasurements: defaulted to false. If set to true, the function
 * will take measurements of the system.
 * @param outputFile: a pointer to a std::ofstream to write our data into
 *
 * @ return: default returns 0.0 (success), if takeMeasurements=true, returns
 * the thermodynamic average spin of the system.
 */
double runMetropolis(Lattice &lattice, const int &numSteps, const double &beta,
                     std::mt19937 &gen, const bool takeMeasurements = false,
                     std::ofstream *outputFile = nullptr);

int main(int argc, char *argv[]) {

  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <equilibirationSteps> <measurementSteps> <temperature>"
              << 'n';
    return 1;
  }
  try {

    const int numEquilibrationSteps = std::stoi(argv[1]);
    const int numMeasurementSteps = std::stoi(argv[2]);
    const double temp = std::stod(argv[3]);
    const double beta = 1.0 / (Const::boltzmann * temp);

    std::random_device rd;
    std::mt19937 gen(rd());

    Lattice lattice(Const::latticeSize,
                    std::vector<double>(Const::latticeSize));

    std::ofstream dataFile("equilibration_data.txt");

    setInitialState(lattice);
    double equilibrated = runMetropolis(lattice, numEquilibrationSteps, beta,
                                        gen, false, &dataFile);
    if (equilibrated == 0.0) {
      double result =
          runMetropolis(lattice, numMeasurementSteps, beta, gen, true);
      std::cout << "<s> = " << result << std::endl;
    }
    dataFile.close();

  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid argument: Please provide integer values for steps."
              << '\n';
    return 1;
  }

  return 0;
}

void setInitialState(Lattice &lattice) {
  for (int i = 0; i < Const::latticeSize; i++) {
    for (int j = 0; j < Const::latticeSize; j++) {
      lattice[i][j] = Const::spin;
    }
  }
}

int periodicIndex(int index, int size) { return (index + size) % size; }

double deltaE(const Lattice &lattice, const int &i, const int &j) {
  double neighborSum = lattice[periodicIndex(i - 1, Const::latticeSize)][j] +
                       lattice[periodicIndex(i + 1, Const::latticeSize)][j] +
                       lattice[i][periodicIndex(j - 1, Const::latticeSize)] +
                       lattice[i][periodicIndex(j + 1, Const::latticeSize)];

  double state{lattice[i][j]};
  double result = 2 * state * (Const::epsilon * neighborSum + Const::magField);
  return result;
}

bool acceptabilityCheck(const double &dE, double &randomNumU,
                        const double &beta) {
  double acceptProb;
  if (dE < 0) {
    return true;
  } else {
    // Boltzmann distribution
    acceptProb = std::exp(-beta * dE);
    if (randomNumU <= acceptProb) {
      return true;
    } else {
      return false;
    }
  }
}
double calcInstTotalSpin(const Lattice &lattice) {
  double totalSpin = 0;
  for (const auto &row : lattice) {
    for (double spin : row) {
      totalSpin += spin;
    }
  }
  return totalSpin;
}

double runMetropolis(Lattice &lattice, const int &numSteps, const double &beta,
                     std::mt19937 &gen, const bool takeMeasurements,
                     std::ofstream *outputFile) {

  std::uniform_int_distribution<> randIPos(0, Const::latticeSize - 1);
  std::uniform_int_distribution<> randJPos(0, Const::latticeSize - 1);
  // Generates random number [0, 1) to compare with acceptance probability
  std::uniform_real_distribution<> randNum(0, 1);

  int numSites{Const::latticeSize * Const::latticeSize};
  double numSweeps{std::floor(numSteps / static_cast<double>(numSites))};
  double totalSysSpin{0.0};

  for (int k = 0; k < numSteps; k++) {

    int iPos{randIPos(gen)};
    int jPos{randJPos(gen)};
    double randNumU{randNum(gen)};
    double dE{deltaE(lattice, iPos, jPos)};
    bool acceptability{acceptabilityCheck(dE, randNumU, beta)};

    if (acceptability == true) {
      lattice[iPos][jPos] *= -1;
    }

    if (k % numSites == 0) {
      if (outputFile != nullptr) {
        *outputFile << (k / numSites) << "," << calcInstTotalSpin(lattice)
                    << '\n';
      }
      if (takeMeasurements) {
        totalSysSpin += calcInstTotalSpin(lattice);
      }
    }
  }

  if (takeMeasurements) {
    return totalSysSpin / (numSweeps * numSites);
  }

  return 0.0;
}
