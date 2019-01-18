#include <naive/naive.h>
#include <core/util.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>


namespace bob {
  void Naive::calculate(
      double input,
      std::vector<Reading>& outputs,
      std::unique_ptr<Profile> const& profile,
      int current_time_step,
      float& current_glucose,
      float& current_carbs) {
    Reading r;
    current_glucose = glucose_diffusion(
       input,
       profile->glucose,
       profile->irr,
       profile->gly_idx,
       current_time_step);
    profile->glucose = current_glucose;

    current_carbs = carbohydrate_diffusion(
      input,
      profile->gly_idx,
      current_time_step);
    profile->carbs = current_carbs;

    if (!profile->acceptable_glucose()) {
      double profile_glucose = profile->glucose;
      profile->irr = profile->modulate_irr(profile_glucose);
    }

    auto reading = r.make_reading(profile, current_time_step);
    std::cout << reading << std::endl;
    outputs.push_back(reading);
  }

  std::vector<Reading> Naive::engine(std::unique_ptr<Profile> const& profile) {
    profile->show_run_stats();
    show_logo();
    std::vector<Reading> outputs;

    float current_glucose, current_carbs;
    int days = profile->days * 24 * 60;

    for (int current_time = 1; current_time < days; ++current_time) {
      auto f = std::async(std::launch::async, [] {
        std::string input = "0.01";
        if (std::cin >> input) {
          return std::stod(input);
        } else { return std::stod(input); }
      });

      if (f.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
        auto input = f.get();
        std::cout << "Got food input of: " << input << "g of carbs" << std::endl;

        calculate(input, outputs, profile, current_time, current_glucose, current_carbs);
      } else {
        std::cout << "No input provided, using default" << std::endl;
        calculate(0.001, outputs, profile, current_time, current_glucose, current_carbs);
      }
    }

    return outputs;
  }

  int Naive::simulation(int argc, char** argv) {
    if (argc < 2) {
      show_logo();
      std::cout << OPTS << std::endl;
      return EXIT_SUCCESS;
    }

    std::unique_ptr<Profile> p(new Profile(std::string(argv[1])));
    std::vector<Reading> outputs = engine(p);
    std::cout << outputs[0] << std::endl;

    return EXIT_SUCCESS;
  }
} // namespace bob
