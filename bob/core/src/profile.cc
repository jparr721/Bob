#include <core/profile.h>
#include <core/util.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace bob {
  Profile::Profile(std::string const& profile_path) {
    indexer(profile_path);
  }

  void Profile::operator=(Profile const& p) {
    time_between_meals = p.time_between_meals;
    interval = p.interval;
    carbs = p.carbs;
    glucose = p.glucose;
    irr = p.irr;
    gly_idx = p.gly_idx;
    meals = p.meals;
  }

  bool Profile::operator==(Profile const& p) const {
    return time_between_meals == p.time_between_meals &&
      interval == p.interval &&
      carbs == p.carbs &&
      glucose == p.glucose;
  }

  void Profile::show_run_stats() const {
    std::cout << "\n\nThanks for stopping by! Here's the run agenda for today:" << std::endl;
    std::cout << "Time between meals: " << time_between_meals << " minutes" << std::endl;
    std::cout << "Total runtime (in days): " << days << std::endl;
    std::cout  << "Diabetes: " << has_diabetes << std::endl;
  }

  std::ostream& operator<<(std::ostream& os, Profile const& p) {
    os << "{ " <<
      p.time_between_meals <<
      ", " <<
      p.interval <<
      ", " <<
      p.carbs <<
      ", " <<
      p.glucose <<
      ", " <<
      p.irr <<
      ", " <<
      p.gly_idx <<
      ", [";
    auto meals = p.meals;
    for (auto i = 0u; i < meals.size() - 1; ++i)
      os << meals[i] << ", ";
    os << meals[meals.size()] << " ";
    os << "] }";
    return os;
  }

  void Profile::indexer(std::string const& profile_path) {
    Util u;
    std::vector<std::string> lines = u.read_file(profile_path);

    // Load in our initial profile stats
    std::vector<std::string> initial_stats = u.split_by_space(lines[0]);
    if (!(initial_stats[0] == "I")) throw std::invalid_argument("Invalid profile sequence(initial stats)");
    try {
      std::cout << "unpacking: " << initial_stats.size() << " items" << std::endl;
      time_between_meals = std::stoi(initial_stats[1]);
      carbs = std::stof(initial_stats[2]);
      glucose = std::stof(initial_stats[3]);
      irr = std::stof(initial_stats[4]);
      gly_idx = std::stof(initial_stats[5]);
      interval = std::stoi(initial_stats[6]);
      has_diabetes = u.string_to_bool(initial_stats[7]);
      days = std::stoi(initial_stats[8]);
    } catch (std::out_of_range const& oor) {
      std::cerr << "Invalid number of initial configs supplied, check your config file" << std::endl;
      return;
    }
    std::cout << "items unpacked, moving on with setup..." << std::endl;
    // Cannot set to 0 or it breaks the algorithm
    if (has_diabetes) {
      std::cout << "Diabetes detected changing irr to 0.0001" << std::endl;
      irr = 0.0001;
      std::cout << "irr is now: " << irr << std::endl;
    }

    // Load in the thresholds
    std::vector<std::string> thresholds = u.split_by_space(lines[1]);
    if (!(thresholds[0] == "T")) throw std::invalid_argument("Invalid profile sequence(thresholds)");
    try {
      std::cout << "unpacking: " << thresholds.size() << " items" << std::endl;
      maximum_upper_threshold = std::stoi(thresholds[1]);
      upper_threshold = std::stoi(thresholds[2]);
      lower_threshold = std::stoi(thresholds[3]);
      maximum_lower_threshold = std::stoi(thresholds[4]);
      standard_bolus_negative_multiplier = std::stof(thresholds[5]);
      standard_bolus_positive_multiplier = std::stof(thresholds[6]);
    } catch (std::out_of_range const& oor) {
      std::cerr << "Invalid number of thresholds supplied, check your config file" << std::endl;
      return;
    }
    std::cout << "items unpacked, moving on with setup..." << std::endl;

    // Load in the meals
    std::vector<std::string> meals_string = u.split_by_space(lines[2]);
    if (!(meals_string[0] == "M")) throw std::invalid_argument("Invalid profile sequence(meals)");
    std::cout << "loading: " << meals_string.size() << " meals" << std::endl;

    std::vector<float> meals(meals_string.size() - 1);
    std::transform(meals_string.begin() + 1, meals_string.end(), meals.begin(), [](const std::string& val) {
      return std::stof(val);
    });
    this->meals = meals;

    std::cout << "meals loaded successfully, moving on with sim" << std::endl;
  }

  double Profile::modulate_irr(double glucose) {
    if (glucose >= maximum_upper_threshold)
      return irr * pow(standard_bolus_positive_multiplier, 2);
    else if (glucose < maximum_upper_threshold &&
             glucose >= upper_threshold)
      return irr * standard_bolus_positive_multiplier;
    else if (glucose <= maximum_lower_threshold)
      return irr * pow(standard_bolus_negative_multiplier, 2);
    else
      return irr * standard_bolus_negative_multiplier;
  }

  bool Profile::acceptable_glucose() {
    return glucose >= 75 && glucose >= 105;
  }

  void Profile::modify_insulin_bolus(double bolus) {
    if (bolus <= 0) {
      return;
    }

    irr = std::fmod(bolus, 1.0);
  }

  void Profile::modify_glycemic_index(double gly_idx) {
    if (gly_idx <= 0) {
      return;
    }

    gly_idx = std::fmod(gly_idx, 1.0);
  }
} // namespace bob
