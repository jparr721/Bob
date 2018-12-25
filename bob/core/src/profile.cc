#include <core/profile.h>
#include <core/util.h>

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
      this->time_between_meals = std::stoi(initial_stats[1]);
      this->carbs = std::stof(initial_stats[2]);
      this->glucose = std::stof(initial_stats[3]);
      this->irr = std::stof(initial_stats[4]);
      this->gly_idx = std::stof(initial_stats[5]);
      this->interval = std::stoi(initial_stats[6]);
      this->has_diabetes = std::stoi(initial_stats[7]);
      this->days = std::stoi(initial_stats[8]);
    } catch (std::out_of_range const& oor) {
      std::cerr << "Invalid number of initial configs supplied, check your config file" << std::endl;
      return;
    }
    // Cannot set to 0 or it breaks the algorithm
    if (has_diabetes) this->irr = 0.0001;


    // Load in the thresholds
    std::vector<std::string> thresholds = u.split_by_space(lines[1]);
    if (!(thresholds[0] == "T")) throw std::invalid_argument("Invalid profile sequence(thresholds)");
    try {
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

    // Load in the meals
    std::vector<std::string> meals_string = u.split_by_space(lines[2]);
    std::vector<float> meals;
    meals.reserve(meals_string.size());

    for (auto meal = meals.begin() + 1; meal != meals.end(); ++meal) {
      meals.push_back(*meal);
    }
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
