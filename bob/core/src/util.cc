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

  void Util::write_to_file(std::vector<std::string> output_vector) const {
    std::ostringstream filename;

    // Get time of current run
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    filename << "Run" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

    std::ofstream runfile(filename.str());

    std::cout << "Done writing to file..." << std::endl;
  }

  bool Util::string_to_bool(std::string bool_val) const {
    return bool_val != "0";
  }
} // namespace bob
