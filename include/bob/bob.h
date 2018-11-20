#pragma once

#include <string>
#include <vector>

namespace bob {
  class Bob {
    public:
      Bob(std::string infile="profiles/input.txt", std::string outfile="profiles/output.txt");
      Bob(float carbs, float glucose);
      ~Bob() = default;
      void RunSimulation(
          int time,
          float glycemic_index,
          float insulin_release_rate,
          int interval);

      void RunBasic(
          int time,
          float glycemic_index,
          float insulin_release_rate,
          int interval);

      void set_initial_carbs(float carbs);
      float get_initial_carbs();

      void set_initial_glucose(float glucose);
      float get_initial_glucose();

    private:
      std::string infile;
      std::string outfile;
      float initial_carbs;
      float initial_glucose;
      const std::string appversion = "0.7.0";
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
