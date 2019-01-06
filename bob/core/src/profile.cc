#include <core/profile.h>
#include <core/util.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace bob {
  Profile::Profile(std::string const& profile_path) {
    this->indexer(profile_path);
  }

  void Profile::operator=(Profile const& p) {
    this->time_between_meals = p.get_time();
    this->interval = p.get_interval();
    this->carbs = p.get_carbs();
    this->glucose = p.get_glucose();
    this->irr = p.get_irr();
    this->gly_idx = p.get_gly_idx();
    this->meals = p.get_meals();
  }

  bool Profile::operator==(Profile const& p) const {
    return this->time_between_meals == p.get_time() &&
      this->interval == p.get_interval() &&
      this->carbs == p.get_carbs() &&
      this->glucose == p.get_glucose();
  }

  std::string Profile::make_run_stats() const {
    std::stringstream stats;
    stats << "\n\nThanks for stopping by! Here's the run agenda for today:\n"
      << "Time between meals: " << this->time_between_meals << " minutes\n"
      << "Total runtime (in days): " << this->days << "\n"
      << "Diabetes: " << this->has_diabetes << "\n";

    return stats.str();
  }

  std::ostream& operator<<(std::ostream& os, Profile const& p) {
    os << "{ " <<
      p.get_time() <<
      ", " <<
      p.get_interval() <<
      ", " <<
      p.get_carbs() <<
      ", " <<
      p.get_glucose() <<
      ", " <<
      p.get_irr() <<
      ", " <<
      p.get_gly_idx() <<
      ", [";
    auto meals = p.get_meals();
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
      this->time_between_meals = std::stoi(initial_stats[1]);
      this->carbs = std::stof(initial_stats[2]);
      this->glucose = std::stof(initial_stats[3]);
      this->irr = std::stof(initial_stats[4]);
      this->gly_idx = std::stof(initial_stats[5]);
      this->interval = std::stoi(initial_stats[6]);
      this->has_diabetes = u.string_to_bool(initial_stats[7]);
      this->days = std::stoi(initial_stats[8]);
    } catch (std::out_of_range const& oor) {
      std::cerr << "Invalid number of initial configs supplied, check your config file" << std::endl;
      return;
    }
    std::cout << "items unpacked, moving on with setup..." << std::endl;
    // Cannot set to 0 or it breaks the algorithm
    if (has_diabetes) {
      std::cout << "Diabetes detected changing irr to 0.0001" << std::endl;
      this->irr = 0.0001;
      std::cout << "irr is now: " << this->irr << std::endl;
    }

    // Load in the thresholds
    std::vector<std::string> thresholds = u.split_by_space(lines[1]);
    if (!(thresholds[0] == "T")) throw std::invalid_argument("Invalid profile sequence(thresholds)");
    try {
      std::cout << "unpacking: " << thresholds.size() << " items" << std::endl;
      this->maximum_upper_threshold = std::stoi(thresholds[1]);
      this->upper_threshold = std::stoi(thresholds[2]);
      this->lower_threshold = std::stoi(thresholds[3]);
      this->maximum_lower_threshold = std::stoi(thresholds[4]);
      this->standard_bolus_negative_multiplier = std::stof(thresholds[5]);
      this->standard_bolus_positive_multiplier = std::stof(thresholds[6]);
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
    if (glucose >= this->maximum_upper_threshold)
      return this->irr * pow(this->standard_bolus_positive_multiplier, 2);
    else if (glucose < this->maximum_upper_threshold &&
             glucose >= this->upper_threshold)
      return this->irr * this->standard_bolus_positive_multiplier;
    else if (glucose <= this->maximum_lower_threshold)
      return this->irr * pow(this->standard_bolus_negative_multiplier, 2);
    else
      return this->irr * this->standard_bolus_negative_multiplier;
  }

  bool Profile::acceptable_glucose() {
    return this->glucose >= 75 && this->glucose >= 105;
  }

  void Profile::set_irr(double irr) {
    this->irr = irr;
  }

  void Profile::modify_insulin_bolus(double bolus) {
    if (bolus <= 0) {
      return;
    }

    this->irr = std::fmod(bolus, 1.0);
  }

  void Profile::modify_glycemic_index(double gly_idx) {
    if (gly_idx <= 0) {
      return;
    }

    this->gly_idx = std::fmod(gly_idx, 1.0);
  }

  void Profile::set_glucose(double glucose) {
    this->glucose = glucose;
  }

  void Profile::set_carbs(double carbs) {
    this->carbs = carbs;
  }

  int Profile::get_time() const {
    return this->time_between_meals;
  }

  int Profile::get_interval() const {
    return this->interval;
  }

  int Profile::get_days() const {
    return this->days;
  }

  double Profile::get_carbs() const {
    return this->carbs;
  }

  double Profile::get_glucose() const {
    return this->glucose;
  }

  double Profile::get_irr() const {
    return this->irr;
  }

  double Profile::get_gly_idx() const {
    return this->gly_idx;
  }

  std::vector<float> Profile::get_meals() const {
    return this->meals;
  }
} // namespace bob
