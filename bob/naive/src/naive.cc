#include <core/util.h>
#include <naive/naive.h>

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace bob {
  void Naive::adjust_insulin_bolus(double bolus) {
    if (bolus <= 0) {
      return;
    }
    this->bolus = std::fmod(bolus, 1.0);
  }

  double Naive::get_insulin_bolus() {
    return this->bolus;
  }

  void Naive::simulate(const std::string profile) {
    this->show_logo();
    Util u;
    // Load in our user profile
    std::vector<std::string> lines = u.read_file(profile);
    int time, interval;
    double carbs, glucose, bolus_init, glycemic_index;

    std::vector<std::string> initial_vals = u.split_by_space(lines[0]);
    time = std::stoi(initial_vals[0]);
    interval = std::stoi(initial_vals[5]);
    carbs = std::stof(initial_vals[1]);
    glucose = std::stof(initial_vals[2]);
    bolus_init = std::stof(initial_vals[3]);
    glycemic_index = std::stof(initial_vals[4]);

    std::vector<std::string> new_carbs_string = u.split_by_space(lines[1]);
    std::vector<float> new_carbs;
    new_carbs.reserve(new_carbs_string.size());

    // Convert to float vector
    // TODO Clean up this routine
    for (const auto& carb : new_carbs_string) {
      new_carbs.push_back(std::stof(carb));
    }

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

  void Naive::verify_insulin_dispersion(float current_glucose) {
    if (current_glucose > 550) {
      std::cout << "DEFINTELY DEAD" << std::endl;
    }
    //TODO -- Try to make this cleaner? Maybe?
    if (current_glucose >= this->UPPER_THRESHOLD &&
        current_glucose < this->MAXIMUM_UPPER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * this->STANDARD_BOLUS_POSITIVE_MULTIPLIER);
    } else if (current_glucose > this->MAXIMUM_UPPER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * pow(this->STANDARD_BOLUS_POSITIVE_MULTIPLIER, 5));
    } else if (current_glucose <= this->LOWER_THRESHOLD &&
        current_glucose > this->MAXIMUM_LOWER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * this->STANDARD_BOLUS_NEGATIVE_MULTIPLIER);
    } else if (current_glucose < this->MAXIMUM_LOWER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * pow(this->STANDARD_BOLUS_NEGATIVE_MULTIPLIER, 5));
    }
  }
} // namespace bob
