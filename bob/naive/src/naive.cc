#include <core/util.h>
#include <naive/naive.h>

#include <unordered_map>

namespace bob {
  void Naive::adjust_insulin_bolus(double bolus) const {
    if (bolus <= 0) {
      return;
    }
    this->bolus = bolus;
  }

  double get_insulin_bolus() {
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

    for (;;) {
      int i = 0;
      int total_entries = new_carbs.size();
      float glucose_level = this->glucose_diffusion(
          new_carbs[i % total_entries],
          this->bolus
    }

  }
} // namespace bob
