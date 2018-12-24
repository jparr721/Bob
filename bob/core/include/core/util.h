#pragma once

#include <string>
#include <vector>

namespace bob {
  class Util {
    public:
      Util() = default;
      ~Util() = default;

      void write_to_file(std::vector<std::string> output_vector) const;
      template<typename T>
      void log(std::string label, T data) const;

      std::vector<std::string> read_file(std::string path) const;
      std::vector<std::string> split_by_space(std::string input) const;
  };
} // namespace bob
