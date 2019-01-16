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
  std::vector<Reading> Naive::engine(std::unique_ptr<Profile> const& profile) {
    profile->show_run_stats();
    show_logo();
    std::vector<Reading> outputs;

    float current_glucose, current_carbs;
    int days = profile->days;
    int time = profile->time_between_meals;

    for (int i = 0; i < days; ++i) {
      for (int j = 1; j < time; ++j) {
        auto f = std::async(std::launch::async, [] {
          std::string input = "0.01";
          if (std::cin >> input) {
            return std::stod(input);
          } else { return std::stod(input); }
        });

        if(f.wait_for(std::chrono::seconds(2)) != std::future_status::ready) {
          std::cout << "Waiting for input on main thread..." << std::endl;
        }

        auto input = f.get();
        std::cout << "Got food input of: " << input << "g of carbs" << std::endl;
        Reading r;

        current_glucose = glucose_diffusion(
           input,
           profile->glucose,
           profile->irr,
           profile->gly_idx,
           j);
        profile->glucose = current_glucose;

        current_carbs = carbohydrate_diffusion(
          input,
          profile->gly_idx,
          j);
        profile->carbs = current_carbs;

        if (!profile->acceptable_glucose()) {
          double profile_glucose = profile->glucose;
          profile->irr = profile->modulate_irr(profile_glucose);
        }

        auto reading = r.make_reading(profile, j * i);
        std::cout << reading << std::endl;
        outputs.push_back(reading);
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
