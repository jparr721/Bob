#pragma once

#include <core/core.h>
#include <core/reading.h>
#include <core/profile.h>

#include <memory>

namespace bob {
  class Naive : public Core {
    public:
      const std::string OPTS = "Bob Naive\n usage: BobNaive <profile_path>";

      void cycle();

      int simulation(int argc, char** argv);

      std::vector<Reading> engine(std::unique_ptr<Profile> const& profile);
  };
} // namespace bob
