#include <core/util.h>
#include <naive/naive.h>

#include <cmath>
#include <unordered_map>

namespace bob {
  void Naive::adjust_insulin_bolus(double bolus) const {
    if (bolus <= 0) {
      return;
    }
    this->bolus = bolus;
  }

  double Naive::get_insulin_bolus() {
    return this->bolus;
  }

  void Naive::simulate(std::string profile) {
    this->show_logo();
    Util u;
    // Load in our user profile
    auto lines = u.read_file(profile);
    int time, interval;
    double carbs, glucose, bolus, glycemic_index;
    time = std::stoi(lines[0][0]);
    interval = std::stoi(lines[0][5]);
    carbs = std::atof(lines[0][1]);
    glucose = std::atof(lines[0][2]);
    bolus_init = std::atof(lines[0][3]);
    glycemic_index = std::atof(lines[0][4]);

    if (

    std::vector<int> new_carbs(lines.size() - 2);

    for (auto i = 1u; i < lines.size(); ++i) {
      new_carbs.push_back(lines[0][i]);
    }

    float glucose_level, carb_level;
    // Loop forever
    for (int i = 0;; +=i) {
      int total_entries = new_carbs.size();

      // Runs for each time in the interval
      for (int j = 0; j < time; ++j) {
        glucose_level = this->glucose_diffusion(
            new_carbs[i % total_entries],
            glucose,
            this->bolus,
            this->glycemic_index,
            i);
        carb_level = this->carbohydrate_diffusion(
            new_carbs[i % total_entries],
            this->bolus,
            this->glycemic_index,
            i);
        this->verify_insulin_dispersion(glucose_level);
      }
    }
  }

  void Naive::verify_insulin_dispersion(float current_glucose) {
    //TODO -- Try to make this cleaner? Maybe?
    if (current_glucose >= this->UPPER_THRESHOLD &&
        current_glucose < this->MAXIMUM_UPPER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * this->STANDARD_BOLUS_POSITIVE_MULTIPLIER);
    } else if (current_glucose > this->MAXIMUM_UPPER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * pow(this->STANDARD_BOLUS_POSITIVE_MULTIPLIER, 2));
    } else if (current_glucose <= this->LOWER_THRESHOLD &&
        current_glucose > this->MAXIMUM_LOWER_THRESHOLD) {
      this->adjust_insulin_bolus(this->bolus * this->STANDARD_BOLUS_NEGATIVE_MULTIPLIER);
    } else {
      this->adjust_insulin_bolus(this->bolus * pow(this->STANDARD_BOLUS_NEGATIVE_MULTIPLIER, 2));
    }
  }
} // namespace bob
