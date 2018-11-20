#pragma once

#include <string>
#include <vector>

namespace bob {
  class Util {
    public:
      Util() = default;
      ~Util() = default;

      std::vector<std::string> read_file(std::string filename);
  };
} // namespace bob
