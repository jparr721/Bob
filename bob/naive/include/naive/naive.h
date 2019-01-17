#pragma once

#include <core/core.h>
#include <core/reading.h>
#include <core/profile.h>

#include <memory>

namespace bob {
  class Naive : public Core {
    public:
      const std::string OPTS = "Bob Naive\n usage: BobNaive <profile_path>";

      void calculate(
          double input,
          std::vector<Reading>& outputs,
          std::unique_ptr<Profile> const& profile,
          int current_time_step,
          float& current_glucose,
          float& current_carbs);

      int simulation(int argc, char** argv);

      std::vector<Reading> engine(std::unique_ptr<Profile> const& profile);
  };
} // namespace bob
