#include <core/core.h>

#include <iostream>

int main(int argc, char** argv) {
  int time, interval;
  float initial_carbs, initial_glucose, insulin_rate, glycemic_index;
  std::string infile, outfile;

  switch (argc) {
    case 7: {
      std::cout << "Running basic simulation..." << std::endl;
      time = std::stoi(argv[1]);
      initial_carbs = std::stof(argv[2]);
      initial_glucose = std::stof(argv[3]);
      insulin_rate = std::stof(argv[4]);
      glycemic_index = std::stof(argv[5]);
      interval = std::stoi(argv[6]);
      break;
    }
    case 1:
    case 2:
      if (argv[1] && std::string(argv[1]) == "--help") {
        std::cout << argv[1] << std::endl;
        usage();
        break;
      }
      std::cout << "No options specified, ruinnning with default file locations" << std::endl;
      break;
    case 3:
      infile = argv[1];
      outfile = argv[2];
      break;
    default:
      usage();
      break;
  }

  return EXIT_SUCCESS;
}
