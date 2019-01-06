#pragma once

#include <core/core.h>
#include <core/reading.h>
#include <core/profile.h>

namespace bob {
  class Naive : public Core {
    public:
      Naive() = default;
      ~Naive() = default;

      std::vector<Reading> naive_sim(std::unique_ptr<Profile> const& profile);
      const std::string OPTS =
          R"(
Bob Naive Model

usage:

BobNaive <profile>
          )";
  };
} // namespace bob
