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
    this->show_logo();
    std::vector<Reading> outputs;
    Util u;

    float current_glucose, current_carbs;
    std::vector<float> meals = profile->get_meals();
    int meal_count = meals.size();
    int days = profile->get_days();
    int time = profile->get_time();

    for (int i = 0; i < days; ++i) {
      for (int j = 1; j < time; ++j) {
        Reading r;
        current_glucose = glucose_diffusion(
           meals[std::fmod(i, meal_count)],
           profile->get_glucose(),
           profile->get_irr(),
           profile->get_gly_idx(),
           j);
        profile->set_glucose(current_glucose);
        /* u.log<double>("Current glucose", profile->get_glucose()); */
        current_carbs = carbohydrate_diffusion(
          meals[std::fmod(i, meal_count)],
          profile->get_gly_idx(),
          j);
        profile->set_carbs(current_carbs);
        /* u.log<double>("Current carbs", profile->get_carbs()); */
        if (!profile->acceptable_glucose()) {
          double profile_glucose = profile->get_glucose();
          profile->set_irr(profile->modulate_irr(profile_glucose));
        }
        /* u.log<double>("Current insulin release rate", profile->get_irr()); */
        outputs.push_back(r.make_reading(profile, j * i));
      }
    }

    return outputs;
  }
} // namespace bob
