 /* Copyright 2018- GVSU DEN Research Lab
 *
 * Licensed under the GNU Public License, Version 3.0
 * you may not use this file except in compliance with
 * the license. You may obtain a copy of this license
 * at:
 *
 *   https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * DOC
 * Core is a class that defines the main engine
 * for Bob to run off of. This code will be inhereted into
 * the necessary models and implemented there
 *
 * Abbreviations: irr - Insulin Release Rate
 *                gly_index - Glyecmic Index
 * *****************************************************/

#pragma once
#include <core/profile.h>
#include <core/reading.h>

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace bob {
  class Core {
    public:
      Core() = default;
      Core(int carbs, int glucose) : initial_carbs(carbs), initial_glucose(glucose) {};
      ~Core() = default;

      float carbohydrate_diffusion(float carbs, float glycemic_index, int time) const;
      float glucose_diffusion(float carbs, float glucose, float irr, float gly_index, int time) const;

      void usage(const std::string opts) const;
      void show_logo() const;

      const std::string appversion = "4.8.0";
      const std::string bob_logo =
                  R"(
                        |  _ \      | |
                        | |_) | ___ | |__
                        |  _ < / _ \| '_ \
                        | |_) | (_) | |_) |
                        |____/ \___/|_.__/
                    )";

    private:
      std::string infile;
      std::string outfile;
      float initial_carbs;
      float initial_glucose;
  };
} // namespace bob
