#pragma once

#include <string>
#include <vector>

namespace bob {
  class Util {
    public:
      Util() = default;
      ~Util() = default;

      std::vector<std::string> read_file(std::string filename);

      std::vector<std::string> format_data(
          std::vector<float> carbs,
          std::vector<float> glucose,
          int time,
          int interval);

      void write_to_file(std::vector<std::string> output_vector) const;

  };
} // namespace bob
