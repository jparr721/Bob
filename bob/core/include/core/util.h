#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <core/reading.h>

namespace bob {
  class Util {
    public:
      void write_to_file(std::vector<Reading> output_vector) const;

      template<typename T>
      void log(std::string label, T data) const {
        std::cout << label << ": " << data << std::endl;
      }

      std::vector<std::string> read_file(std::string path) const;
      std::vector<std::string> split_by_space(std::string input) const;

      bool string_to_bool(std::string bool_val) const;
  };
} // namespace bob
