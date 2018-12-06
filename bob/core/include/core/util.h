#pragma once

#include <string>
#include <vector>

namespace bob {
  class Util {
    public:
      Util() = default;
      ~Util() = default;

      void write_to_file(std::vector<std::string> output_vector) const;

      std::vector<std::string> read_file(std::string path) const;
      std::vector<std::string> format_data(
          std::vector<float> carbs,
          std::vector<float> glucose,
          int time,
          int interval) const;
      std::vector<std::string> split_by_space(std::string input) const;

  };
} // namespace bob
