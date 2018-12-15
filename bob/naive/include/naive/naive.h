#pragma once

#include <core/core.h>
#include <core/profile.h>

namespace bob {
  class Naive : public Core {
    public:
      Naive() = default;
      ~Naive() = default;

      auto naive_sim [](Profile const& profile)->void;
      void runner();
      const std::string OPTS =
          R"(
Bob Naive Model

BobNaive <profile>
          )";
  };
} // namespace bob
