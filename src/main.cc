#include <bob/bob.h>

#include <iostream>

void usage() {
  const std::string usage_str =
    R"(
    Bob           The Coolest Guy Around

      bob <time> <initial_carbs> <initial_glucose> <insulin_rate> <glucemic_index> <interval>
        -- Runs an instance of the simuation in a single case with no historical considerations

      bob [input.txt] [output.txt]
        -- Runs a stream simulation from an input file and put the output in the output file
           to facilitate interpretation by the RNN.
        -- Default input: input.txt
        -- Default output: output.txt
    )";

   std::cout << usage_str << std::endl;
}

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

      bob::Bob bobby(initial_carbs, initial_glucose);
      bobby.RunBasic(time, glycemic_index, insulin_rate, interval);
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
