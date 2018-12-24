#include <naive/naive.h>
#include <core/util.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

// Idea; make a reading creator function to store previous outputs
// to make the naive predictor more intelligent...

namespace bob {
  std::queue<Reading> Naive::naive_sim(std::unique_ptr<Profile> const& profile) {
    this->show_logo();
    std::queue<Reading> outputs;
    Util u;

    float current_glucose, current_carbs;
    std::vector<float> meals = profile->get_meals();
    size_t meal_count = meals.size();

    // Idea: logger class that takes a map of data labels, then
    // inside of here just print based on the label via a built
    // in print() function that will be formatted accoring to the
    // map...
    for (int i = 1; i < profile->get_days(); ++i) {
      for (int j = 1; j < profile->get_time(); ++j) {
        Reading r;
        current_glucose = this->glucose_diffusion(
           meals[i % meal_count],
           profile->get_glucose(),
           profile->get_irr(),
           profile->get_gly_idx(),
           j);
        profile->set_glucose(current_glucose);
        u.log<double>("Current glucose", profile->get_glucose());
        current_carbs = this->carbohydrate_diffusion(
          meals[i % meal_count],
          profile->get_gly_idx(),
          j);
        profile->set_carbs(current_carbs);
        u.log<double>("Current carbs", profile->get_carbs());
        if (!profile->acceptable_glucose()) {
          double profile_glucose = profile->get_glucose();
          profile->set_irr(profile->modulate_irr(profile_glucose));
        }
        u.log<double>("Current insulin release rate", profile->get_irr());
        outputs.push(r.make_reading(profile, j * i));
      }
    }

    return outputs;
  }
} // namespace bob
