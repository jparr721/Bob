#include <core/reading.h>
#include <core/util.h>
#include <naive/naive.h>

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

// Idea; make a reading creator function to store previous outputs
// to make the naive predictor more intelligent...

namespace bob {
  auto Naive::naive_sim [](Profile const& profile)->void {
    this->show_logo();

    float current_glucose, current_carbs;
    size_t meal_count = profile.meals.size();

    // Idea: logger class that takes a map of data labels, then
    // inside of here just print based on the label via a built
    // in print() function that will be formatted accoring to the
    // map...
    for (int i = 1; i < profile.days; ++i) {
      for (int j = 1; j < profile.get_time(); ++j) {
        current_glucose = this->glucose_diffusion(
           profile.meals[i % meal_count],
           profile.glucose,
           profile.irr,
           profile.gly_idx,
           j];
        profile.glucose = current_glucose;
        current_carbs = this->carbohydrate_diffusion(
          profile.meals[i % meal_count],
          profile.gly_idx,
          j];
        // TODO(jparr721) Finish this impl
        // TODO(jparr721) Add reading class impl
      }
    }
  }
  void Naive::simulate(const std::string profile) {
    this->show_logo();

    float glucose_level, carb_level;
    // Loop forever
    std::cout << "Initialization complete, running simulation..." << std::endl;
    for (int i = 1; i < 2; ++i) {
      std::cout << "Initialization complete, running simulation..." << std::endl;
      int total_entries = new_carbs.size();

      // Runs for each time in the interval
      for (int j = 1; j < time; ++j) {
        std::cout << "Time Elapsed: " << j << " minutes" << std::endl;
        glucose_level = this->glucose_diffusion(
            new_carbs[i % total_entries],
            glucose,
            this->bolus,
            this->glycemic_index,
            j);
        glucose = glucose_level;
        std::cout << "Glucose level currently is: " << glucose << std::endl;
        carb_level = this->carbohydrate_diffusion(
            new_carbs[i % total_entries],
            this->glycemic_index,
            j);
        carbs = carb_level;
        std::cout << "Carb level currently is: " << carbs << std::endl;

        // Our "dumb" predictor to adjust insulin release rates
        /* this->verify_insulin_dispersion(glucose_level); */
        std::cout << "Current insulin release rate: " << this->bolus << std::endl;
        std::cout << "------------------------------" << std::endl;
      }
    }
  }
} // namespace bob
