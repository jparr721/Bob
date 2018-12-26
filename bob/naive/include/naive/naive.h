#pragma once

#include <core/core.h>
#include <core/reading.h>
#include <core/profile.h>

#include <queue>

namespace bob {
  class Naive : public Core {
    public:
      Naive() = default;
      ~Naive() = default;

      std::queue<Reading> naive_sim(std::unique_ptr<Profile> const& profile);
      const std::string OPTS =
          R"(
Bob Naive Model

BobNaive <profile>
          )";
  };
} // namespace bob
