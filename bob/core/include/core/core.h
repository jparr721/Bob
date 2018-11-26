/**
 * Copyright 2018- GVSU DEN Research Lab
 *
 * Licensed under the GNU Public License, Version 3.0
 * you may not use this file except in compliance with
 * the license. You may obtain a copy of this license
 * at:
 *
 * https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * DOC
 * Core is an abstract class that defines the main engine
 * for Bob to run off of. This code will be inhereted into
 * the necessary models and implemented there
 * *****************************************************/

#pragma once

#include <string>
#include <vector>

namespace bob {
  class Core {
    public:
      Core(int carbs, int glucose) : initial_carbs(carbs), initial_glucose(glucose) {};
      ~Core() = default;
      virtual void run(int time, float glycemic_index, float insulin_rate, int interval) = 0;

      void set_initial_carbs(float carbs);
      float get_initial_carbs();

      void set_initial_glucose(float glucose);
      float get_initial_glucose();

    private:
      std::string infile;
      std::string outfile;
      float initial_carbs;
      float initial_glucose;
      const std::string appversion = "1.0.0";
      const std::string bob_logo =
                  R"(
                    |  _ \      | |
                    | |_) | ___ | |__
                    |  _ < / _ \| '_ \
                    | |_) | (_) | |_) |
                    |____/ \___/|_.__/
                    )";

      void show_logo() const;

      std::vector<float> carbohydrate_diffusion(
          int time,
          float carbs,
          float glycemic_index,
          int interval) const;

      std::vector<float> glucose_diffusion(
          int time,
          float carbs,
          float glycemic_index,
          float insulin_release_rate,
          float glucose,
          int interval,
          std::vector<float> carb_dist) const;

      std::vector<std::string> format_data(std::vector<float> carbs, std::vector<float> glucose, int time, int interval);
      void write_to_file(std::vector<std::string> output_vector) const;

  };
} // namespace bob
