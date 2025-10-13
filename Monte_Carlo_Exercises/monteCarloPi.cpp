#include <iostream>
#include <random>

bool checkInCircle(double xPos, double yPos) {
  // std::cout << "xpos = " << xPos << '\n';
  // std::cout << "ypos = " << yPos << '\n';

  double result{(xPos * xPos) + (yPos * yPos)};

  // std::cout << "Result = " << result << '\n';

  if (result > 1) {
    return false;
  }
  return true;
}

int main(void) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> rndXPos(-1.0, 1.0);
  std::uniform_real_distribution<> rndYPos(-1.0, 1.0);

  double totalPoints{1000000.0};
  double validPoints{0.0};
  for (int i = 0; i < totalPoints + 1; i++) {
    if (checkInCircle(rndXPos(gen), rndYPos(gen))) {
      validPoints += 1.0;
    } else {
      continue;
    }
  }
  std::cout << "valid points = " << validPoints << '\n';

  double approxPi = 4 * (validPoints / totalPoints);

  std::cout << "Approximate Monte Carlo pi = " << approxPi << std::endl;

  return 0;
}
