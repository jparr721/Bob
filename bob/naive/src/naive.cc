#include <naive/naive.h>
#include <core/util.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// Idea; make a reading creator function to store previous outputs
// to make the naive predictor more intelligent...

namespace bob {
  /* template<bool with_logging> */
  std::vector<Reading> Naive::naive_sim(std::unique_ptr<Profile> const& profile) {
    std::string stats = profile->make_run_stats();
    std::cout << stats << std::endl;
    show_logo();
    std::vector<Reading> outputs;
    Util u;

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
        u.log<double>("Current glucose", profile->glucose);
        current_carbs = carbohydrate_diffusion(
          profile->meals[std::fmod(i, meal_count)],
          profile->gly_idx,
          j);
        profile->carbs = current_carbs;
        u.log<double>("Current carbs", profile->carbs);
        if (!profile->acceptable_glucose()) {
          double profile_glucose = profile->glucose;
          profile->irr = profile->modulate_irr(profile_glucose);
        }
        u.log<double>("Current insulin release rate", profile->irr);
        outputs.push_back(r.make_reading(profile, j * i));
      }
    }

    return outputs;
  }
} // namespace bob
