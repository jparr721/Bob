#include <bob/bob.hpp>

#include <iostream>

int main(int argc, char** argv) {
  if (argc < 7) {
    std::cerr << "usage: bob <time> <initial_carbs> <initial_glucose> <insulin_rate> <glycemic_index> <interval>" << std::endl;
    return EXIT_FAILURE;
  }

  int time = std::stoi(argv[1]);
  float initial_carbs = std::stof(argv[2]);
  float initial_glucose = std::stof(argv[3]);
  float insulin_rate = std::stof(argv[4]);
  float glycemic_index = std::stof(argv[5]);
  int interval = std::stoi(argv[6]);

  bob::Bob bobby(initial_carbs, initial_glucose);
  bobby.RunSimulation(time, glycemic_index, insulin_rate, interval);

  return EXIT_SUCCESS;
}
