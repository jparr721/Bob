#include <core/util.h>

#include <sstream>
#include <fstream>

namespace bob {
  std::vector<std::string> Util::read_file(std::string filename) {
    std::ifstream input(filename);
    std::vector<std::string> data;
    std::string line;

    while (std::getline(input, line)) {
      std::istringstream iss(line);
      data.push_back(iss.str());
    }

    return data;
  }
} // namespace bob
