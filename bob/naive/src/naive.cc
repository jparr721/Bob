#include <naive/naive.h>
#include <core/util.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>


namespace bob {
  std::vector<Reading> Naive::engine(std::unique_ptr<Profile> const& profile) {
    std::string stats = profile->make_run_stats();
    std::cout << stats << std::endl;
    show_logo();
    std::vector<Reading> outputs;

    float current_glucose, current_carbs;
    int meal_count = profile->meals.size();
    int days = profile->days;
    int time = profile->time_between_meals;

    for (int i = 0; i < days; ++i) {
      for (int j = 1; j < time; ++j) {
        Reading r;

        current_glucose = glucose_diffusion(
           profile->meals[std::fmod(i, meal_count)],
           profile->glucose,
           profile->irr,
           profile->gly_idx,
           j);
        profile->glucose = current_glucose;

        current_carbs = carbohydrate_diffusion(
          profile->meals[std::fmod(i, meal_count)],
          profile->gly_idx,
          j);
        profile->carbs = current_carbs;

        if (!profile->acceptable_glucose()) {
          double profile_glucose = profile->glucose;
          profile->irr = profile->modulate_irr(profile_glucose);
        }

        outputs.push_back(r.make_reading(profile, j * i));
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
