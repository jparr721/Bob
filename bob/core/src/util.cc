#include <core/util.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <sstream>

namespace bob {
  std::vector<std::string> Util::read_file(std::string path) const {
    std::cout << "Opening: " << path << std::endl;
    std::ifstream input(path);
    if (!input.good()) throw std::invalid_argument("Invalid path specified");
    std::vector<std::string> data;
    std::string line;

    while (std::getline(input, line)) {
      std::istringstream iss(line);
      data.push_back(iss.str());
    }

    return data;
  }

  std::vector<std::string> Util::split_by_space(std::string input) const {
    std::istringstream iss(input);
    return std::vector<std::string> {std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>{}};
  }

  std::vector<std::string> Util::format_data(
      std::vector<float> carbs,
      std::vector<float> glucose,
      int time,
      int interval) const {
    std::vector<std::string> output_vector;
    // Before storage, verify uniform sizing on input vectors
    if (carbs.size() != glucose.size()) {
      throw new std::invalid_argument("Input vectors are not the same size, output will be improper");
    }

    // Use a string stream to build our file lines
    std::ostringstream run_header, data_line;
    run_header << "Carbohydrates over " << time << " min " << "Glucose over " << time << " min";

    data_line << "Initial Levels: " << carbs[0] << " carbs " << glucose[0] << " glucose" << std::endl;
    output_vector.push_back(data_line.str());
    int timestamp = 0;

    for (auto it1 = carbs.begin(), it2 = glucose.begin();
        it1 != carbs.end() && it2 != glucose.end(); ++it1, ++it2) {
      data_line << timestamp << " minutes" << *it1 << " " << timestamp << " minutes: " << *it2;
      output_vector.push_back(data_line.str());
      timestamp += interval;
    }

    return output_vector;
  }

  void Util::write_to_file(std::vector<std::string> output_vector) const {
    std::ostringstream filename;

    // Get time of current run
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    filename << "Run" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

    std::ofstream runfile(filename.str());

    std::cout << "Done writing to file..." << std::endl;
  }
} // namespace bob
